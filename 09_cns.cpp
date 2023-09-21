#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>

// AES encryption function
void AESEncrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    // Create and initialize the context
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    // Perform the encryption
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    ciphertext_len = len;

    // Finalize the encryption
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
}

// AES decryption function
void AESDecrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    // Create and initialize the context
    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    // Perform the decryption
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len);
    plaintext_len = len;

    // Finalize the decryption
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    // Example key (128 bits) and IV (Initialization Vector, 128 bits)
    unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    unsigned char iv[16] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};

    // Example plaintext
    unsigned char plaintext[] = "Hello, AES!123";

    // Determine the length of the plaintext
    int plaintext_len = strlen(reinterpret_cast<const char*>(plaintext));

    // Calculate the size needed for the ciphertext buffer
    int ciphertext_len = plaintext_len + 16 - (plaintext_len % 16);

    // Create buffers for ciphertext and decrypted text
    unsigned char ciphertext[ciphertext_len];
    unsigned char decrypted[ciphertext_len];

    // Encrypt the plaintext
    AESEncrypt(plaintext, plaintext_len, key, iv, ciphertext);

    // Decrypt the ciphertext
    AESDecrypt(ciphertext, ciphertext_len, key, iv, decrypted);

    // Print the results
    std::cout << "Plaintext: " << plaintext << std::endl;
    std::cout << "Ciphertext (hex): ";
    for (int i = 0; i < ciphertext_len; ++i) {
        std::cout << std::hex << static_cast<int>(ciphertext[i]);
    }
    std::cout << std::endl;
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}
