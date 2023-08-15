#include "button.h"
#include "constants.h"


//keyboard struct; u8 mode variable corresponding to one of the keyboard modes; look in constants.h for further details
//array of buttons and three single buttons used to change keyboard mode
typedef struct{
  u8 mode;

  Button buttons[KEYBOARD_KEYS];
  Button KB_mode_upper_case;
  Button KB_mode_lower_case;
  Button KB_mode_symbols;

  bool disabled;
}Keyboard_element;


u8 mode_to_offset(u8 mode, u8 i);
void update_buttons(Keyboard_element *keyboard);

Keyboard_element init_keyboard(u8 y);
void draw_keyboard(Keyboard_element *keyboard);
u8 get_pressed_key(Keyboard_element *keyboard, u8 x, u8 y);
char get_character(Keyboard_element *keyboard, u8 x, u8 y);

void enable_keyboard(Keyboard_element*keyboard);
void disable_keyboard(Keyboard_element*keyboard);
