#include <stdint.h>
#include <openssl/aes.h>
#include <stdio.h>
// #include <openssl/evp.h>
//#include <string.h>
#define OPENSSL_API_COMPAT 0x10100000L
int main() {
  printf("this is a test\n");
  uint8_t key[16] = { 0 };
  uint8_t plaintext[16] = { 0 };
  uint8_t ciphertext[16] = { 0 };

  AES_KEY aes_key;
  AES_set_encrypt_key(key, 128, &aes_key);
  AES_encrypt(plaintext, ciphertext, &aes_key);
  //EVP_aes_128_ccm();

  printf("this is test for aes_encrypt\n\n");
  for(int i=0;i<16;i++)
    printf("%02x ", ciphertext[i]);

  return 0;
}
