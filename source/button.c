#include <nds.h>
#include "button.h"
#include "constants.h"

//init button struct given its position and number of sprite in spritesheet defining its graphics
Button init_button(u8 x, u8 y, u8 id){
  Button button;
  button.x = x;
  button.y = y;
  button.sprite = init_sprite(id, false);
  button.disabled = false;
	return button;
}

//change button graphics; takes in sprite number in spritesheet defining new graphics
void update_button_offset(Button* button, u8 new_offset){
  update_sprite_offset(&button->sprite, new_offset);
}

//draw button sprite; Takes in OAM number to be set
void draw_button(Button *button, u8 id){
  if(!button->disabled)
    draw_sprite(&button->sprite, id, button->x, button->y);
}

//checks if button is checked given position that is touched
bool is_button_pressed(Button *button, u8 x, u8 y){
  if(button->disabled)return false;
  if(x < button->x)return false;
  if(x > button->x + BUTTON_SIZE)return false;
  if(y < button->y)return false;
  if(y > button->y + BUTTON_SIZE)return false;
  return true;
}

//disable button processing and rendering 
void disable_button(Button*button){
  button->disabled = true;
}

//enable button processing and rendering 
void enable_button(Button*button){
  button->disabled = false;
}
