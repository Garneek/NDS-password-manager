#include <nds.h>
#include <stdio.h>
#include "password_manager_gui.h"

//init console and print GUI base within
PrintConsole init_password_gui(){
  PrintConsole console;
  consoleInit(&console, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
  consoleSetWindow(&console, 1, 1, 30, 23);
  consoleSelect(&console);
  printf("        MAIN PASSWORD\n+============================+\n+============================+           OUTPUT\n+============================+\n+============================+  SEED:                        \n. - Full charset\n  . - Phone charset\n  # - Simple charset\n\nY - Swap charset\nUp - seed + 1\nRight - seed + 10\nDown - seed + 100\nLeft - seed + 1000\nA - reset seed\nB - generate password");
  return console;
}

//print master password when it is updated
void update_password_input_gui(char* pswd, PrintConsole* console){
  consoleSelect(console);
  printf("\x1b[2;0H%s", pswd);
}

//print output password when it is updated
void update_password_output_gui(char* pswd, PrintConsole* console){
  consoleSelect(console);
  printf("\x1b[6;0H%s", pswd);
}

//print seed when it is updated
void update_seed_gui(u32 seed, PrintConsole* console){
  consoleSelect(console);
  printf("\x1b[8;7H          ");
  printf("\x1b[8;7H%lu", seed);
}

//print what character set is in use 
void update_character_set_gui(u8 charset_len, PrintConsole* console){
  consoleSelect(console);
  if (charset_len == NUMBER_OF_CHARACTERS_FULL)printf("\x1b[10;0H  # - Full charset\n  . - Phone charset\n  . - Simple charset\n");
  else if (charset_len == NUMBER_OF_CHARACTERS_PHONE)printf("\x1b[10;0H  . - Full charset\n  # - Phone charset\n  . - Simple charset\n");
  else if (charset_len == NUMBER_OF_CHARACTERS_SIMPLE)printf("\x1b[10;0H  . - Full charset\n  . - Phone charset\n  # - Simple charset\n");
}
