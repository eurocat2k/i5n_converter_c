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
        // printf("%c %c %c %c\n", src[i], src[i + 1], src[i + 2], src[i + 3]);
#ifdef NOINDEXOF
        // 0
        if (src[i] >= 65 && src[i] <= 90) {
            ch0 = src[i] - 64;
        } else if (src[i] == 32) {
            ch0 = src[i];
        } else if (src[i] >= 48 && src[i] <= 57) {
            ch0 = src[i];
        }
        // 1
        if (src[i + 1] >= 65 && src[i + 1] <= 90) {
            ch1 = src[i + 1] - 64;
        } else if (src[i + 1] == 32) {
            ch1 = src[i + 1];
        } else if (src[i + 1] >= 48 && src[i + 1] <= 57) {
            ch1 = src[i + 1];
        }
        // 2
        if (src[i + 2] >= 65 && src[i + 2] <= 90) {
            ch2 = src[i + 2] - 64;
        } else if (src[i + 2] == 32) {
            ch2 = src[i + 2];
        } else if (src[i + 2] >= 48 && src[i + 2] <= 57) {
            ch2 = src[i + 2];
        }
        // 3
        if (src[i + 3] >= 65 && src[i + 3] <= 90) {
            ch3 = src[i + 3] - 64;
        } else if (src[i + 3] == 32) {
            ch3 = src[i + 3];
        } else if (src[i + 3] >= 48 && src[i + 3] <= 57) {
            ch3 = src[i + 3];
        }
#else
        ch0 = indexOf((int)src[i]);
        ch1 = indexOf((int)src[i + 1]);
        ch2 = indexOf((int)src[i + 2]);
        ch3 = indexOf((int)src[i + 3]);
#endif
        printf(BYTE_TO_BINARY_PATTERN " %2d %c\n", BYTE_TO_BINARY(ch0), ch0, sixbitstable[ch0]);
        printf(BYTE_TO_BINARY_PATTERN " %2d %c\n", BYTE_TO_BINARY(ch1), ch1, sixbitstable[ch1]);
        printf(BYTE_TO_BINARY_PATTERN " %2d %c\n", BYTE_TO_BINARY(ch2), ch2, sixbitstable[ch2]);
        printf(BYTE_TO_BINARY_PATTERN " %2d %c\n", BYTE_TO_BINARY(ch3), ch3, sixbitstable[ch3]);
        // 1 [000001][01] c0 & 0x3f << (2) | ch1 0x3f >> (4)
        // 2 [0101][0000] ch1 & 0xf << (4) | ch2 0x3f >> (4)
        // 3 [01][110111] ch2 & 0x3 << (6) | ch3 & 0x3f
        // 4 [000010][01] c4 & 0x3f << (2) | ch5 0x3f >> (4)
        // 5 [1010][1100] ch5 & 0xf << (4) | ch6 0x3f >> (4)
        // 6 [11][100000] ch6 & 0x3 << (6) | ch7 & 0x3f
        dst[j] = (unsigned char)ch0 << 2 | (unsigned char)(ch1 & 0x30) >> 4;
        dst[j+1] = ((unsigned char)ch1 & 0x0f) << 4 | ((unsigned char)(ch2) & 0x3f) >> 2;
        dst[j+2] = ((unsigned char)ch2 & 0x3) << 6 | ((unsigned char)(ch3) & 0x3f);
    }
}

void i5n_decode(char *const dst, const char *src, size_t len) {
    if (NULL == dst || NULL == src || len != I5N_SIXBITS_SIZE) {
        return;
    }
    for (int i = 0, j = 0; i < len; i += 3, j += 4) {
        printf("%d\n", (unsigned char)src[i] >> 2);
        printf("%d\n", (src[i] & 0x3) << 4 | ((unsigned char)src[i + 1]) >> 4);
        printf("%d\n", (src[i+1] & 0xf) << 6 | (unsigned char)src[i+2]);
        printf("%d\n", src[i + 2] & 0x3f);
        dst[j] = sixbitstable[(unsigned char)src[i] >> 2];
        dst[j+1] = sixbitstable[(src[i] & 0x3) << 4 | ((unsigned char)src[i + 1] & 0xf0) >> 4];
        dst[j+2] = sixbitstable[(src[i+1] & 0x0f) << 2 | ((unsigned char)src[i+2] & 0x30) >> 6];
        dst[j + 3] = sixbitstable[src[i + 2] & 0x3f];
        // Top 6 bits of byte i
        // int value1 = array[i] >> 2;
        // Bottom 2 bits of byte i, top 4 bits of byte i+1
        // int value2 = ((array[i] & 0x3) << 4) | (array[i + 1] >> 4);
        // Bottom 4 bits of byte i+1, top 2 bits of byte i+2
        // int value3 = ((array[i + 1] & 0xf) << 2) | (array[i + 2] >> 6);
        // Bottom 6 bits of byte i+2
        // int value4 = array[i + 2] & 0x3f;

        //   printf("%d\n", src[i+1] << 4 | src[i + 2] >> 4);
        // printf("%d %c\n", (unsigned char)src[i] >> 2, sixbitstable[(unsigned
        // char)src[i] >> 2]); dst[j] = sixbitstable[(unsigned char)src[i] >> 2];
        // printf("%d %c\n", (src[i] & 0x03) << 6 | (unsigned char)src[i+1] >> 4,
        // sixbitstable[(src[i] & 0x03) << 4 | (unsigned char)src[i+1] >> 4]);
        // dst[j + 1] = sixbitstable[(src[i] & 0x03) << 2 | (unsigned
        // char)src[i+1] >> 4]; printf("%d %c\n", (src[i+1] & 0x3) << 2 |
        // (unsigned char)src[i+2] >> 6, sixbitstable[(src[i+1] & 0x0f) << 2 |
        // (unsigned char)src[i+2] >> 6]); dst[j + 2] = sixbitstable[(src[i + 1] &
        // 0x0f) << 2 | (unsigned char)src[i + 2] >> 6]; printf("%c\n",
        // sixbitstable[src[i + 2] & 0x3f]); dst[j + 3] = sixbitstable[src[i + 2]
        // & 0x3f];
    }
    return;
}
