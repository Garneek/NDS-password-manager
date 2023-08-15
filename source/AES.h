#ifndef AES_DEFINED
#define AES_DEFINED

//Struct for state of 128 bits AES 
typedef struct{
  u32 A,B,C,D;
} AES_state; 

//Struct for key for single round of 128 bits AES
typedef struct{
  u32 A,B,C,D;
} AES_key;

AES_state init_AES_state(u32 A, u32 B, u32 C, u32 D);
AES_key init_AES_key(u32 A, u32 B, u32 C, u32 D);

void AES_encrypt(AES_state* state, AES_key* key);
void AES_decrypt(AES_state* state, AES_key* key);

void key_rot(AES_key* key);
void state_rot(AES_state* state);

#endif
