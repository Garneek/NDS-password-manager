#include <nds.h>
#include "sprite.h"


//spritesheet of size 32x32x200 by default
extern const unsigned int spritesheetTiles[SPRITESHEETS_SIZE];


//init sprite struct; takes in sprite offset in spritesheet and whether the sprite is on top screen or not;
//sets offset and allocates gfx
Sprite init_sprite(u16 offset, bool top_screen){
  Sprite sprite;
  sprite.offset = SPRITE_SIZE * offset;
  sprite.disabled = false;
  sprite.gfx_frame = (u8*)spritesheetTiles;
  if (top_screen)sprite.gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
  else sprite.gfx = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
  sprite.top_screen = top_screen;
  return sprite;
}

//updates offset; takes in sprite number in spritesheet
void update_sprite_offset(Sprite* sprite, u8 new_offset){
  sprite->offset = SPRITE_SIZE * new_offset;
}

//draws sprite on screen; takes in OAM number and position;
void draw_sprite(Sprite* sprite, u8 id, u8 x, u8 y){
  if(!sprite->disabled){
    u8* pos = sprite->gfx_frame + sprite->offset;
  	dmaCopy(pos, sprite->gfx, SPRITE_SIZE);
    if(sprite->top_screen){
      oamSet(&oamMain,
        id,
        x, y,
        0, 15,
        SpriteSize_32x32,
        SpriteColorFormat_256Color,
        sprite->gfx,
        -1, false, false, false, false, false);
    }else{
    	oamSet(&oamSub,
    		id,
    		x, y,
    		0, 15,
    		SpriteSize_32x32,
    		SpriteColorFormat_256Color,
    		sprite->gfx,
    		-1, false, false, false, false, false);
    }
  }
}
//disables sprite rendering
void disable_sprite(Sprite*sprite){
  sprite->disabled = true;
}
//enables sprite rendering
void enable_sprite(Sprite*sprite){
  sprite->disabled = false;
}
