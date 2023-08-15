#ifndef BUTTON_DEFINED
#define BUTTON_DEFINED

#include "sprite.h"

//Struct defining button; contains button position, sprite defining it and its state
typedef struct {
  u8 x, y;
  Sprite sprite;
  bool disabled;
} Button;

Button init_button(u8 x, u8 y, u8 id);
void update_button_offset(Button* button, u8 new_offset);
void draw_button(Button *button, u8 id);
void enable_button(Button*button);
void disable_button(Button*button);
bool is_button_pressed(Button *button, u8 x, u8 y);

#endif
