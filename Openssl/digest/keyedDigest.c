#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

#define MAXLEN 64

int main() {

    OpenSSL_add_all_algorithms();
    unsigned char key[] = "this_is_my_secret";

    FILE *file = fopen("file.txt", "r");

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_PKEY *hkey = EVP_PKEY_new_mac_key(EVP_PKEY_HMAC, NULL, key, strlen(key));

    EVP_DigestInit(ctx, EVP_sha512());

    EVP_DigestUpdate(ctx, key, strlen(key));

    unsigned char data[MAXLEN];
    int dsize;
    while ((dsize = fread(data, 1, MAXLEN, file)) > 0) {
        EVP_DigestUpdate(ctx, data, dsize);
    }

    EVP_DigestUpdate(ctx, key, strlen(key));

    unsigned int siglen = EVP_MD_get_size(EVP_sha512());
    unsigned char sigret[siglen];

    EVP_DigestFinal(ctx, sigret, &siglen);

    for (int i = 0; i < siglen; ++i) {
        printf("%02x", sigret[i]);
    }
    printf("\n");


}