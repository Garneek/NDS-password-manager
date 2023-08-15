#include <nds.h>
#include "generate_password.h"

const u8 characters_full[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";
const u8 characters_phone[] = " !\"#$&'()*+,-.0123456789:;=?@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz|";
const u8 characters_simple[] = " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


void randomizer_round(AES_state* state, AES_key* key){
  AES_encrypt(state, key);
  state_rot(state);
  key_rot(key);
  AES_decrypt(state, key);
  state_rot(state);
}

void init_AES_key_value(AES_key* key){
  AES_state state = init_AES_state(4217005973,410003557,4123461119,294968239);
  u8 i;
  for (i = 0; i < 255; i++)
    randomizer_round(&state, key);
  key->A = state.A;
  key->B = state.B;
  key->C = state.C;
  key->D = state.D;
}


u8 character_to_number(u8 chr){
  u8 p1 = 0, p2 = NUMBER_OF_CHARACTERS_FULL - 1;
  while (p2 - p1 > 1){
    if (characters_full[(p1 + p2) / 2] < chr)p1 = (p1 + p2) / 2;
    else p2 = (p1 + p2) / 2;
  }
  if(characters_full[p2] == chr) return p2;
  return p1;
}

void main_pswd_to_states_1(char* pswd, AES_state* state, AES_key* key, u32 seed, u8 password_lenght){
  u8 i;
  for(i = 0; i < password_lenght; i++){
    if((i & 7) == 0){
      state->A <<= 7;
      state->A |= character_to_number(pswd[i]);
    }else if((i & 7) == 1){
      state->B <<= 7;
      state->B |= character_to_number(pswd[i]);
    }else if((i & 7) == 2){
      state->C <<= 7;
      state->C |= character_to_number(pswd[i]);
    }else if((i & 7) == 3){
      state->D <<= 7;
      state->D |= character_to_number(pswd[i]);
    }else if((i & 7) == 4){
      key->A <<= 7;
      key->A |= character_to_number(pswd[i]);
    }else if((i & 7) == 5){
      key->B <<= 7;
      key->B |= character_to_number(pswd[i]);
    }else if((i & 7) == 6){
      key->C <<= 7;
      key->C |= character_to_number(pswd[i]);
    }else if((i & 7) == 7){
      key->D <<= 7;
      key->D |= character_to_number(pswd[i]);
    }
  }
  key->A ^= seed;
  state->D ^= seed;
  init_AES_key_value(key);
  for(i = 0; i < 255; i++)randomizer_round(state,key);
}

void main_pswd_to_states_2(char* pswd, AES_state* state, AES_key* key, u32 seed, u8 password_lenght){
  u8 i;
  for(i = 0; i < password_lenght; i++){
    if((i & 7) == 0){
      key->D <<= 7;
      key->D |= character_to_number(pswd[i]);
    }else if((i & 7) == 1){
      key->C <<= 7;
      key->C |= character_to_number(pswd[i]);
    }else if((i & 7) == 2){
      key->B <<= 7;
      key->B |= character_to_number(pswd[i]);
    }else if((i & 7) == 3){
      key->A <<= 7;
      key->A |= character_to_number(pswd[i]);
    }else if((i & 7) == 4){
      state->D <<= 7;
      state->D |= character_to_number(pswd[i]);
    }else if((i & 7) == 5){
      state->C <<= 7;
      state->C |= character_to_number(pswd[i]);
    }else if((i & 7) == 6){
      state->B <<= 7;
      state->B |= character_to_number(pswd[i]);
    }else if((i & 7) == 7){
      state->A <<= 7;
      state->A |= character_to_number(pswd[i]);
    }
  }
  key->D ^= seed;
  state->A ^= seed;
  init_AES_key_value(key);
  for(i = 0; i < 255; i++)randomizer_round(state,key);
}

void main_password_to_final(char* pswd, char* pswd_output, u32 seed, u8 charset_len, u8 password_lenght){
  AES_state state1 = init_AES_state(0,0,0,0);
  AES_key key1 = init_AES_key(0,0,0,0);
  AES_state state2 = init_AES_state(0,0,0,0);
  AES_key key2 = init_AES_key(0,0,0,0);
  u8 i, j = 0;
  u32 x = state1.A;
  main_pswd_to_states_1(pswd,&state1, &key1, seed + 1, password_lenght);
  main_pswd_to_states_2(pswd,&state2, &key2, seed + 1, password_lenght);

  for(i = 0; i < password_lenght; i++){
    while(x % charset_len == 0){
      x /= charset_len;
      if(x == 0){
        j++;
        if(j == 1)x += state1.B;
        else if(j == 2)x += state1.C;
        else if(j == 3)x += state1.D;
        else if(j == 4)x += state2.A;
        else if(j == 5)x += state2.B;
        else if(j == 6)x += state2.C;
        else if(j == 7)x += state2.D;
      }
    }
    if(charset_len == NUMBER_OF_CHARACTERS_FULL)pswd_output[i] = characters_full[x % charset_len];
    if(charset_len == NUMBER_OF_CHARACTERS_PHONE)pswd_output[i] = characters_phone[x % charset_len];
    if(charset_len == NUMBER_OF_CHARACTERS_SIMPLE)pswd_output[i] = characters_simple[x % charset_len];

    x /= charset_len;
    if(x == 0){
      j++;
      if(j == 1)x += state1.B;
      else if(j == 2)x += state1.C;
      else if(j == 3)x += state1.D;
      else if(j == 4)x += state2.A;
      else if(j == 5)x += state2.B;
      else if(j == 6)x += state2.C;
      else if(j == 7)x += state2.D;
    }
  }
}
/*
int main(){
  u8 password[30] = "                              ";
  u8 password_output[30] = "                              ";

  main_password_to_final(password, password_output, 1, 63, 30);

  printf("%s", password_output);

}*/
