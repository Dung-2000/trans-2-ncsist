#include <openssl/evp.h>

void encrypt_ccm(const unsigned char *key, const unsigned char *iv, const unsigned char *aad,
                 int aad_len, const unsigned char *plaintext, int plaintext_len,
                 unsigned char *ciphertext, unsigned char *tag) {

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_ccm(), NULL, NULL, NULL);

    // Set IV length and tag length
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN, 12, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, 16, NULL);

    // Initialize key and IV
    EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv);

    // Add AAD
    int len;
    EVP_EncryptUpdate(ctx, NULL, &len, aad, aad_len);

    // Encrypt plaintext
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);

    // Finalize and get  tag
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_GET_TAG, 16, tag);

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
  encrypt_ccm();
  return 1;
}
