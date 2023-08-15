#ifndef SPRITE_DEFINED
#define SPRITE_DEFINED
#include "constants.h"

//sprite struct; offset is the pixel number which starts sprite in spritesheet; top_screen determines where sprite is rendered;
//gfx and gfx_frame are graphics memory and pointer to spritesheet
typedef struct{
  u32 offset;
  bool disabled;
  bool top_screen;
  u16* gfx;
  u8* gfx_frame;
} Sprite;

Sprite init_sprite(u16 offset, bool top_screen);
void update_sprite_offset(Sprite* sprite, u8 new_offset);
void draw_sprite(Sprite*sprite, u8 id, u8 x, u8 y);
void disable_sprite(Sprite*sprite);
void enable_sprite(Sprite*sprite);

#endif
