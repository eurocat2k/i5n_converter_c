#include "include/i5n.h"
#include <stdio.h>
#include <string.h>
static const char sixbitstable[] = "#ABCDEFGHIJKLMNOPQRSTUVWXYZ##### ###############0123456789######";

int indexOf(int ch) {
    char *p = strchr(sixbitstable, ch);
    if (NULL != p) {
        return (p - sixbitstable);
    }
    return -1;
}

void i5n_encode(char *const dst, const char *src, size_t len) {
    if (NULL == dst || NULL == src || len != I5N_ASCII_SIZE) {
        return;
    }
    unsigned char ch0, ch1, ch2, ch3;
    for (int i = 0, j = 0; i < len; i += 4, j += 3) {
        ch0 = indexOf((int)src[i]);
        ch1 = indexOf((int)src[i + 1]);
        ch2 = indexOf((int)src[i + 2]);
        ch3 = indexOf((int)src[i + 3]);
        dst[j]     = (ch0 << 2 | (ch1 & 0x30) >> 4);
        dst[j + 1] = ((ch1 & 0x0f) << 4 | (ch2 & 0x3f) >> 2);
        dst[j + 2] = ((ch2 & 0x03) << 6 | ch3);
        // printf(" 0x%02x", (unsigned char)dst[j]);
        // printf(" 0x%02x", (unsigned char)dst[j + 1]);
        // printf(" 0x%02x\n\n", (unsigned char)dst[j + 2]);
    }
}

void i5n_decode(char *const dst, const char *src, size_t len) {
    if (NULL == dst || NULL == src || len != I5N_SIXBITS_SIZE) {
        return;
    }
    for (int i = 0, j = 0; i < len; i += 3, j += 4) {
        printf("%d\n", (unsigned char)src[i] >> 2);
        printf("%d\n", ((unsigned char)src[i] & 0x3) << 4 | ((unsigned char)src[i + 1] & 0xf0) >> 4);
        printf("%d\n", ((unsigned char)src[i+1] & 0xf) << 2 | (unsigned char)(src[i+2] & 0xc0) >> 6);
        printf("%d\n", (unsigned char)src[i + 2] & 0x3f);
        dst[j]   = sixbitstable[(unsigned char)src[i] >> 2];
        dst[j+1] = sixbitstable[((unsigned char)src[i] & 0x3) << 4 | ((unsigned char)src[i+1] & 0xf0) >> 4];
        dst[j+2] = sixbitstable[((unsigned char)src[i+1] & 0x0f) << 2 | ((unsigned char)src[i+2] & 0xC0) >> 6];
        dst[j+3] = sixbitstable[((unsigned char)src[i+2] & 0x3f)];
    }
    return;
}
