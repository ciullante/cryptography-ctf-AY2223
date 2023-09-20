#include <stdio.h>
#include <string.h>

#include <openssl/evp.h>


#define ENCRYPT 1
#define DECRYPT 0

unsigned char *hexToBin(char *hex) {
    unsigned char *bin = calloc(strlen(hex) / 2, sizeof(unsigned char));
    for (int i = 0; i < strlen(hex) / 2; ++i) {
        sscanf(&hex[2 * i], "%2hhX", &bin[i]);
    }
    return bin;
}

char *binToHex(unsigned char *bin, int len){
    char *hex = calloc(len * 2, sizeof(char));
    for (int i = 0; i < len; ++i) {
        sprintf(&hex[i * 2], "%02X", bin[i]);
    }
    return hex;
}

int main()
{

//int EVP_EncryptInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type, const unsigned char *key, const unsigned char *iv); 
//int EVP_EncryptFinal(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl); 

//  int EVP_DecryptInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type, const unsigned char *key, const unsigned char *iv); 
//  int EVP_DecryptFinal(EVP_CIPHER_CTX *ctx, unsigned char *outm, int *outl); 

//  int EVP_CipherInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type, const unsigned char *key, const unsigned char *iv, int enc); 
//  int EVP_CipherFinal(EVP_CIPHER_CTX *ctx, unsigned char *outm, int *outl); 






    char key[] = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";
    char iv[]  = "11111111111111112222222222222222";
    char ciphertext_hex[] = "8f24b734806a7a7a825a90c8da3912bbecfddcd9036d6914322b60";

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_CipherInit(ctx,EVP_chacha20(), hexToBin(key), hexToBin(iv), DECRYPT);

    // convert hexstring into bytes 
    int ciphertext_len = strlen(ciphertext_hex)/2;
    unsigned char ciphertext_binary[ciphertext_len];
    for(int i = 0; i < ciphertext_len;i++){
        sscanf(&ciphertext_hex[2*i],"%2hhx", &ciphertext_binary[i]);
    }
    for(int i = 0; i < ciphertext_len; i++)
        printf("%02x", ciphertext_binary[i]);
    printf("\n");


    unsigned char decrypted[ciphertext_len]; //may be larger than needed due to padding 

    int update_len, final_len;
    int decrypted_len=0;
    EVP_CipherUpdate(ctx,decrypted,&update_len,ciphertext_binary,ciphertext_len);
    decrypted_len+=update_len;
    printf("update size: %d\n",decrypted_len);

    EVP_CipherFinal_ex(ctx,decrypted+decrypted_len,&final_len);
    decrypted_len+=final_len;

    EVP_CIPHER_CTX_free(ctx);


    printf("Plaintext lenght = %d\n",decrypted_len);
    for(int i = 0; i < decrypted_len; i++)
        printf("%2x", decrypted[i]);
    printf("\n");
    for(int i = 0; i < decrypted_len; i++)
        printf("%c", decrypted[i]);
    printf("\n");


    return 0;
}