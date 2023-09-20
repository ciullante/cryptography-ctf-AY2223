#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

#define MAXLEN 64

int main() {

    OpenSSL_add_all_algorithms();
    unsigned char key[] = "keykeykeykeykeykey";

    FILE *file1 = fopen("file1.txt", "r");
    FILE *file2 = fopen("file2.txt", "r");

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_PKEY *hkey = EVP_PKEY_new_mac_key(EVP_PKEY_HMAC, NULL, key, strlen(key));


    EVP_DigestSignInit(ctx, NULL, EVP_sha256(), NULL, hkey);

    unsigned char data[MAXLEN];
    int dsize;
    while ((dsize = fread(data, 1, MAXLEN, file1)) > 0){
        EVP_DigestSignUpdate(ctx, data, dsize);
    }
    while ((dsize = fread(data, 1, MAXLEN, file2)) > 0){
        EVP_DigestSignUpdate(ctx, data, dsize);
    }

    size_t siglen = EVP_MD_get_size(EVP_sha256());
    unsigned char sigret[siglen];

    EVP_DigestSignFinal(ctx, sigret, &siglen);

    for (int i = 0; i < siglen; ++i) {
        printf("%02x", sigret[i]);
    }
    printf("\n");



}