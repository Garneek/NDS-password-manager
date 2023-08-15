#include <nds.h>
#include "button.h"
#include "constants.h"


Button init_button(u8 x, u8 y, u8 id){
  Button button;
  button.x = x;
  button.y = y;
  button.sprite = init_sprite(id, false);
  button.disabled = false;
	return button;
}

void update_button_offset(Button* button, u8 new_offset){
  update_sprite_offset(&button->sprite, new_offset);
}


void draw_button(Button *button, u8 id){
  if(!button->disabled)
    draw_sprite(&button->sprite, id, button->x, button->y);
}

bool is_button_pressed(Button *button, u8 x, u8 y){
  if(x < button->x)return false;
  if(x > button->x + BUTTON_SIZE)return false;
  if(y < button->y)return false;
  if(y > button->y + BUTTON_SIZE)return false;
  return true;
}

void disable_button(Button*button){
  button->disabled = true;
}

void enable_button(Button*button){
  button->disabled = false;
}
