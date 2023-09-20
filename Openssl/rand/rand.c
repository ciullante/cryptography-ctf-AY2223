#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned char *randOR(unsigned char *rand1, unsigned char *rand2, int len) {
    unsigned char *res = calloc(len, sizeof(unsigned char));
    for (int i = 0; i < len; ++i) {
        res[i] = rand1[i] | rand2[i];
    }
    return res;
}

unsigned char *randAnd(unsigned char *rand1, unsigned char *rand2, int len) {
    unsigned char *res = calloc(len, sizeof(unsigned char));
    printf("SONO QUI: %d\n\n", len);
    for (int i = 0; i < len; ++i) {
        res[i] = rand1[i] & rand2[i];
    }
    return res;
}

unsigned char *randXor(unsigned char *rand1, unsigned char *rand2, int len) {
    unsigned char *res = calloc(len, sizeof(unsigned char));
    for (int i = 0; i < len; ++i) {
        res[i] = rand1[i] ^ rand2[i];
    }
    return res;
}

unsigned char *stringToRand(char *string, int len) {
    unsigned char *rand = calloc((len + 1)/3, sizeof(unsigned char));
    sscanf(&string[0], "%2hhx", &rand[0]);
    for (int i = 0; i < (len + 1) / 3 - 1; ++i) {
        sscanf(&string[i * 3 + 2], "%*c%2hhx", &rand[i + 1]);
    }
    //printf("%s\n", rand);
    return rand;
}

char *randToString(unsigned char *rand, int len) {
    char *string = calloc(len * 3 - 1, sizeof(char));

    sprintf(&string[0], "%02x", rand[0]);
    for (int i = 0; i < len - 1; i++) {
        sprintf(&string[2 + 3 * i], "-%02x", rand[i + 1]);
    }

    //printf("%s\n", string);
    return string;
}

int main() {
    char string1[] = "63-3b-6d-07-65-1a-09-31-7a-4f-b4-aa-ef-3f-7a-55-d0-33-93-52-1e-81-fb-63-11-26-ed-9e-8e-a7-10-f6-63-9d-eb-92-90-eb-76-0b-90-5a-eb-b4-75-d3-a1-cf-d2-91-39-c1-89-32-84-22-12-4e-77-57-4d-25-85-98";
    char string2[] = "92-05-d8-b5-fa-85-97-b6-22-f4-bd-26-11-cf-79-8c-db-4a-28-27-bb-d3-31-56-74-16-df-cb-f5-61-a7-9d-18-c2-63-92-f1-cb-c3-6d-2b-77-19-aa-21-07-8e-fe-8b-1a-4f-7d-70-6e-a4-7b-c8-68-30-43-12-50-30-1e";
    int len_r = (strlen(string1) + 1)/3;
    int len_s = strlen(string1);


    unsigned char *rand1 = stringToRand(string1, len_s);
    unsigned char *rand2 = stringToRand(string2, len_s);


    unsigned char *k1 = randOR(rand1, rand2, 64);
    unsigned char *k2 = randAnd(rand1, rand2, 64);
    unsigned char *key = randXor(k1, k2, 64);

    printf("%s\n", randToString(key, len_r));

}