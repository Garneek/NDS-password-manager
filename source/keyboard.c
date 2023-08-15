#include <nds.h>
#include "keyboard.h"


//characters avilable in upper case mode(altho there is delete button it is yet to be implemented)
const char upper_case_chars[KEYBOARD_KEYS] = "1234567890\bQWERTYUIOPASDFGHJKLZXCVBNM  \n";
//characters avilable in lower case mode
const char lower_case_chars[KEYBOARD_KEYS] = "1234567890\bqwertyuiopasdfghjklzxcvbnm  \n";
//characters avilable in symbols mode
const char symbols_chars[KEYBOARD_KEYS] =    "!\"#$%&'()*+,-./:;<=>\?@[]^_`{|}~XCVBNM  \n";

//takes mode and key number in keyboard; outputs offset of graphics in spritesheet corresponding to that key
u8 mode_to_offset(u8 mode, u8 i){
  if(mode == UPPER_MODE)return i;
  if(mode == LOWER_MODE){
    if(i < 11)return i;
    if(i < 37)return i + 29;
    return i;
  }
  if(i < 31)return i + 66;
  return i;
}

//updates button's offsets and in turn their sprite to correspond with current mode
void update_buttons(Keyboard_element *keyboard){
  u8 i;
  for(i = 0; i < KEYBOARD_KEYS; i++){
    if(i < 11)update_button_offset(&keyboard->buttons[i], mode_to_offset(keyboard->mode, i));
    else if (i < 21)update_button_offset(&keyboard->buttons[i], mode_to_offset(keyboard->mode, i));
    else if (i < 30)update_button_offset(&keyboard->buttons[i], mode_to_offset(keyboard->mode, i));
    else update_button_offset(&keyboard->buttons[i], mode_to_offset(keyboard->mode, i));
  }
}

//init keyboard struct; takes Y coordinate at which keyboard starts
Keyboard_element init_keyboard(u8 y){
  u8 i;
  Keyboard_element keyboard;
  keyboard.mode = UPPER_MODE;

  keyboard.KB_mode_upper_case = init_button(79, 97 + y, 97);
  keyboard.KB_mode_lower_case = init_button(112, 97 + y, 98);
  keyboard.KB_mode_symbols = init_button(145, 97 + y, 99);

  keyboard.disabled = false;
  for(i = 0; i < KEYBOARD_KEYS; i++){
    if(i < 11)keyboard.buttons[i] = init_button(i * 23 + KEYBOARD_BUTTONS_OFFSET, y, mode_to_offset(keyboard.mode,i));
    else if (i < 21)keyboard.buttons[i] = init_button((i - 11) * 23 + KEYBOARD_BUTTONS_OFFSET + 11, y + 23, mode_to_offset(keyboard.mode,i));
    else if (i < 30)keyboard.buttons[i] = init_button((i - 21) * 23 + KEYBOARD_BUTTONS_OFFSET + 16, y + 46, mode_to_offset(keyboard.mode,i));
    else keyboard.buttons[i] = init_button((i - 30) * 23 + KEYBOARD_BUTTONS_OFFSET + 24, y + 69, mode_to_offset(keyboard.mode,i));
  }
  return keyboard;
}

//draws keyboard struct
void draw_keyboard(Keyboard_element *keyboard){
  if(!keyboard->disabled){
    u8 i;
    for(i = 0; i < KEYBOARD_KEYS; i++){
      draw_button(&keyboard->buttons[i], i);
    }
    draw_button(&keyboard->KB_mode_upper_case, KEYBOARD_KEYS);
    draw_button(&keyboard->KB_mode_lower_case, KEYBOARD_KEYS + 1);
    draw_button(&keyboard->KB_mode_symbols, KEYBOARD_KEYS + 2);
  }
}

//returns number of key in keyboard which is currently pressed; 127 if none is;
//checks mode keys and if one is pressed changes mode and graphic's offsets
u8 get_pressed_key(Keyboard_element *keyboard, u8 x, u8 y){
  u8 i;
  for(i = 0; i < KEYBOARD_KEYS; i++){
    if(is_button_pressed(&keyboard->buttons[i], x, y))return i;
  }
  if(is_button_pressed(&keyboard->KB_mode_upper_case, x, y)){
    keyboard->mode = UPPER_MODE;
    update_buttons(keyboard);
  }
  if(is_button_pressed(&keyboard->KB_mode_lower_case, x, y)){
    keyboard->mode = LOWER_MODE;
    update_buttons(keyboard);
  }
  if(is_button_pressed(&keyboard->KB_mode_symbols, x, y)){
    keyboard->mode = SYMBOLS_MODE;
    update_buttons(keyboard);
  }
  return 127;
}

//gets char of key that is pressed; 0 if none is
char get_character(Keyboard_element *keyboard, u8 x, u8 y){
  if(keyboard -> disabled)return 0;
  u8 pressed_key = get_pressed_key(keyboard, x, y);
  //return pressed_key;

  if(pressed_key == 127)return 0;
  if(keyboard->mode == UPPER_MODE)return upper_case_chars[pressed_key];
  if(keyboard->mode == LOWER_MODE)return lower_case_chars[pressed_key];
  return symbols_chars[pressed_key];
}

//enable keyboard processing and rendering
void enable_keyboard(Keyboard_element*keyboard){
  keyboard->disabled = false;
}
//disable keyboard processing and rendering
void disable_keyboard(Keyboard_element*keyboard){
  keyboard->disabled = true;
}
