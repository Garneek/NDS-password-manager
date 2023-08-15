#include "constants.h"

PrintConsole init_password_gui();
void update_password_input_gui(char* pswd, PrintConsole* console);
void update_password_output_gui(char* pswd, PrintConsole* console);
void update_seed_gui(u32 seed, PrintConsole* console);
void update_character_set_gui(u8 charset_len, PrintConsole* console);
