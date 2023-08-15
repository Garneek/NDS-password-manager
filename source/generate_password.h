#include "AES.h"
#include "constants.h"

void randomizer_round(AES_state* state, AES_key* key);
void init_AES_key_value(AES_key* key);
u8 character_to_number(u8 chr);
void main_pswd_to_states_1(char* pswd, AES_state* state, AES_key* key, u32 seed, u8 password_lenght);
void main_pswd_to_states_2(char* pswd, AES_state* state, AES_key* key, u32 seed, u8 password_lenght);
void main_password_to_final(char* pswd, char* pswd_output, u32 seed, u8 charset_len, u8 password_lenght);
