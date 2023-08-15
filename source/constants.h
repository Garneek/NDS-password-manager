//Output password character list size
//Number of characters in full mode
#define NUMBER_OF_CHARACTERS_FULL 94
//Number of characters in phone mode(every character can be typed from main page in standard smartphone keyboard)
#define NUMBER_OF_CHARACTERS_PHONE 83
//Number of characters in simple mode(a-z; A-Z; 0-9)
#define NUMBER_OF_CHARACTERS_SIMPLE 63

//Screen size
#define WIDTH 256
#define HEIGHT 196
//Lenght of both input and output password
#define PASSWORD_LENGHT 30

//Keyboard data:

//number of keys in keyboard
#define KEYBOARD_KEYS 40
//X axis offset
#define KEYBOARD_BUTTONS_OFFSET 2

//arbitrarily chosen number defining:
//when keyboard is in "upper-case" mode
#define UPPER_MODE 0
//when keyboard is in "lower-case" mode
#define LOWER_MODE 1
//when keyboard is in mode displaying symbols
#define SYMBOLS_MODE 2

//size of key in keyboard in pixels
#define BUTTON_SIZE 22

//Graphics data
//size of sprite; 32x32 in this case
#define SPRITE_SIZE 1024
//size of spritesheet; SPRITE_SIZE * amount of sprites
#define SPRITESHEETS_SIZE 1024 * 200
