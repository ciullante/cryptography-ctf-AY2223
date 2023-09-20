#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>

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

int main() {
    char key[] = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
    char iv[] = "11111111111111112222222222222222";
    unsigned char secret[] = "jyS3NIBqenqCWpDI2jkSu+z93NkDbWkUMitg";
    char hex_sec[] = "8f24b734806a7a7a825a90c8da3912bbecfddcd9036d6914322b60";
//    unsigned char *bin_sec = hexToBin(hex_sec);
    int bin_sec_len = strlen(hex_sec)/2;
//    unsigned char *bin_key = hexToBin(key);
//    int bin_key_len = strlen(key)/2;
//    unsigned char *bin_iv = hexToBin(iv);
//    int bin_iv_len = strlen(iv)/2;

    FILE *in = fopen("test.txt", "rb");
    unsigned char bin_sec[1024];
    while (fread(bin_sec, 1, 1024, in) > 0);
    printf("%.*s\n\n", 28, bin_sec);

//    unsigned char bin_sec[strlen(hex_sec)/2];
//    for(int i = 0; i < strlen(hex_sec)/2;i++){
//        sscanf(&hex_sec[2*i],"%2hhx", &bin_sec[i]);
//    }

    unsigned char bin_key[strlen(key)/2];
    for(int i = 0; i < strlen(key)/2;i++){
        sscanf(&key[2*i],"%2hhx", &bin_key[i]);
    }

    unsigned char bin_iv[strlen(iv)/2];
    for(int i = 0; i < strlen(iv)/2;i++){
        sscanf(&iv[2*i],"%2hhx", &bin_iv[i]);
    }

    printf("%.*s\n\n", strlen(key)/2, bin_key);
    printf("HEY%.*s\n\n", strlen(iv)/2, bin_iv);


    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    const EVP_CIPHER *cipher = EVP_chacha20();
    //EVP_DecryptInit(ctx, EVP_chacha20(), bin_key, bin_iv);
    EVP_CipherInit(ctx, cipher, bin_key, bin_iv, 0);



    int outl = 0;
    int size;
    unsigned char out[1024];
    //EVP_DecryptUpdate(ctx, out, &size, bin_sec, bin_sec_len);
    EVP_CipherUpdate(ctx, out, &size, bin_sec, bin_sec_len);
    outl += size;
    EVP_CipherFinal_ex(ctx, out + size, &size);
    outl += size;
    printf("%.*s\n", outl, out);
    printf("%s\n\n", binToHex(out, outl));


}