
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>

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

int main(){
    OpenSSL_add_all_algorithms();
    char sec_hex[] = "c47c3d88f142d8295e6993a74df2cf2aa1d3caa0d535f3a863461bfce34e94fc";
    char key_hex[] = "0123456789ABCDEF0123456789ABCDEF";
    char iv_hex[] = "11111111111111112222222222222222";

    unsigned char *sec_bin = hexToBin(sec_hex);
    int sec_bin_len = strlen(sec_hex)/2;
    unsigned char plain_bin[sec_bin_len];


    for (int i = 0; i < 1000000; ++i) {
        int plain_bin_len = 0;
        const EVP_CIPHER *cipher;
        if((cipher = EVP_get_cipherbynid(i)) == NULL) continue;

        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        EVP_DecryptInit(ctx, cipher, hexToBin(key_hex), hexToBin(iv_hex));

        int size;
        EVP_DecryptUpdate(ctx, plain_bin, &size, sec_bin, sec_bin_len);
        plain_bin_len += size;

        EVP_DecryptFinal_ex(ctx, plain_bin + plain_bin_len, &size);
        plain_bin_len += size;
        EVP_CIPHER_CTX_free(ctx);

        if(!plain_bin_len) continue;
        printf("%s\n", EVP_CIPHER_get0_name(cipher));
        printf("LEN: %d\n%.*s\n", plain_bin_len, plain_bin_len, plain_bin);

        printf("%s\n\n", binToHex(plain_bin, plain_bin_len));
    }




}