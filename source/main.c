#include <nds.h>
#include <stdio.h>
#include <spritesheet.h>

#include "basic_funcs.h"
#include "constants.h"

//touch data
touchPosition touchXY;

//last character typed on keyboard
char character = ' ';
//current master password
char *password = ">............................<";
//current output password
char *password_output = "..............................";
//index of currently modified character in master password
u8 password_pointer = 0;
//lenght of charset for output password
u8 charset_len = 63;
//current seed
u32 seed = 0;

//console and keyboard
PrintConsole cnsl;
Keyboard_element KB;

//initiates everything needed
void prep_step(){
	KB = init_keyboard(8);
	cnsl = init_password_gui(true, 1,1,30,23);
	update_password_input_gui(password, &cnsl);
	update_password_output_gui(password_output, &cnsl);
	update_seed_gui(seed, &cnsl);
	update_character_set_gui(charset_len, &cnsl);
}

//checks if character can be added to master password
bool character_check(){
	if (character == 0)return false;
	if (character == '\b')return false;
	if (password_pointer >= PASSWORD_LENGHT)return false;
	if (character == '\n')return false;
	if (character == ' ') return false;
	return true;
}

//takes keys pressed data; processes inputs and anything behind-the-scenes
void control_step(int keys){
	if (keys & KEY_TOUCH){ //on bottom screen touched
		touchRead(&touchXY);
		character = get_character(&KB, touchXY.px, touchXY.py);

		if(character_check()){ //adds character to master password
			password[password_pointer] = character;
			password_pointer++;
			update_password_input_gui(password, &cnsl);

		}else if(character == '\b' && password_pointer > 0){ //executes "backspace" action
			password_pointer--;
			password[password_pointer] = '.';
			update_password_input_gui(password, &cnsl);
		}
	}	else if (keys & KEY_B){ // generates output password from given data
		main_password_to_final(password, password_output, seed, charset_len, PASSWORD_LENGHT);
		update_password_output_gui(password_output, &cnsl);
	}	else if (keys & KEY_A){ //resets seed
		seed = 0;
		update_seed_gui(seed, &cnsl);
	} else if (keys & KEY_UP){ //adds 1 to seed
		seed++;
		update_seed_gui(seed, &cnsl);
	} else if (keys & KEY_RIGHT){ //adds 10 to seed
		seed += 10;
		update_seed_gui(seed, &cnsl);
	} else if (keys & KEY_DOWN){ //adds 100 to seed
		seed += 100;
		update_seed_gui(seed, &cnsl);
	} else if (keys & KEY_LEFT){ //adds 1000 to seed
		seed += 1000;
		update_seed_gui(seed, &cnsl);
	} else if (keys & KEY_Y){ //scrolls thru character set lenghts
		if (charset_len == NUMBER_OF_CHARACTERS_FULL)charset_len = NUMBER_OF_CHARACTERS_PHONE;
		else if (charset_len == NUMBER_OF_CHARACTERS_PHONE)charset_len = NUMBER_OF_CHARACTERS_SIMPLE;
		else charset_len = NUMBER_OF_CHARACTERS_FULL;
		update_character_set_gui(charset_len, &cnsl);
	}
}

//handles drawing sprites and backgrounds
void drawing_step(){
	draw_keyboard(&KB);
}

//sets up hardware
void setup_hardware(){
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamSub, SpriteMapping_1D_128, false);
	dmaCopy(spritesheetPal, SPRITE_PALETTE_SUB, 512);

	setBackdropColor(ARGB16(1, 10, 10, 10));
	setBackdropColorSub(ARGB16(1, 10, 10, 10));
}
//main
int main(int argc, char** argv) {
	setup_hardware();
	prep_step();

	while(1) {
		swiWaitForVBlank();
		scanKeys();
		u32 keys = keysDown();
		if (keys & KEY_START) break; //quit on start key
		drawing_step();
		control_step(keys);

		oamUpdate(&oamSub);
	}
}
