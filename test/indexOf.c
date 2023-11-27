#include "i5n.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
static const char sixbitstable[] = "#ABCDEFGHIJKLMNOPQRSTUVWXYZ##### ###############0123456789######";

int indexOf(int ch) {
    char *p = strchr(sixbitstable, ch);
    if (NULL != p) {
        return (p - sixbitstable);
    }
    return -1;
}

int main() {
    // char acid[] = "AUA172B ";
    char acid[] = "QTR41U  ";
    uint8_t enc[] = {0x45, 0x44, 0xb4, 0xc5, 0x58, 0x20};
    uint8_t dec[8] = {0};
    uint8_t c;
    printf("DECODING\n");
    for (int i = 0; i < I5N_ASCII_SIZE; i++) {
        printf("indexOf: %c is %02d %02x\n", acid[i], indexOf(acid[i]), indexOf(acid[i]));
    }
    for (int i = 0, j = 0; i < I5N_SIXBITS_SIZE; i += 3, j += 4) {
        printf(BYTE_TO_BINARY_PATTERN" %02x\n", BYTE_TO_BINARY(enc[i]), enc[i]);
        printf(BYTE_TO_BINARY_PATTERN" %02x\n", BYTE_TO_BINARY(enc[i+1]), enc[i+1]);
        printf(BYTE_TO_BINARY_PATTERN" %02x\n", BYTE_TO_BINARY(enc[i+2]), enc[i+2]);

        printf(" %c(%d)", sixbitstable[enc[i] >> 2], enc[i] >> 2);
        printf(" %c(%d)", sixbitstable[(enc[i] & 0x3) << 4 | (enc[i+1] & 0xf0) >> 4], (enc[i] & 0x3) << 4 | (enc[i+1] & 0xf0) >> 4);
        printf(" %c(%d)", sixbitstable[(enc[i+1] & 0x0f) << 2 | (enc[i+2] & 0xC0) >> 6], (enc[i+1] & 0x0f) << 2 | (enc[i+2] & 0xC0) >> 6);
        printf(" %c(%d)\n",  sixbitstable[(enc[i+2] & 0x3f)], (enc[i+2] & 0x3f));
    }
    int tab[] = {17, 20, 18, 52, 49, 21, 32, 32};
    for (int i = 0; i < I5N_ASCII_SIZE; i += 4) {
        printf(" %d", tab[i]);
        printf(" %d", tab[i + 1]);
        printf(" %d", tab[i + 2]);
        printf(" %d", tab[i + 3]);
    }
    printf("\n");
    printf("idx=18: %c\n", sixbitstable[18]);
    for (int i = 0; i < I5N_ASCII_SIZE; i += 4) {
        printf("%c", sixbitstable[tab[i]]);
        printf("%c", sixbitstable[tab[i + 1]]);
        printf("%c", sixbitstable[tab[i + 2]]);
        printf("%c", sixbitstable[tab[i + 3]]);
    }
    printf("\n");
    printf("\nENCODING\n");
    for (int i = 0, j = 0; i < I5N_ASCII_SIZE; i += 4, j += 3) {
    //   printf(BYTE_TO_BINARY_PATTERN" %2d 0x%02x\n", BYTE_TO_BINARY(sixbitstable[indexOf(enc[i])]) >> 2, sixbitstable[indexOf(enc[i])] >> 2, sixbitstable[indexOf(enc[i])] >> 2);
        printf(" %d %c "BYTE_TO_BINARY_PATTERN"\n", indexOf(acid[i]), sixbitstable[indexOf(acid[i])], BYTE_TO_BINARY(indexOf(acid[i])));
        printf(" %d %c "BYTE_TO_BINARY_PATTERN"\n", indexOf(acid[i+1]), sixbitstable[indexOf(acid[i+1])], BYTE_TO_BINARY(indexOf(acid[i+1])));
        printf(" %d %c "BYTE_TO_BINARY_PATTERN"\n", indexOf(acid[i+2]), sixbitstable[indexOf(acid[i+2])], BYTE_TO_BINARY(indexOf(acid[i+2])));
        printf(" %d %c "BYTE_TO_BINARY_PATTERN"\n", indexOf(acid[i+3]), sixbitstable[indexOf(acid[i+3])], BYTE_TO_BINARY(indexOf(acid[i+3])));

        enc[j] = indexOf(acid[i]) << 2 | (indexOf(acid[i+1]) & 0x30) >> 4;
        enc[j + 1] = (indexOf(acid[i+1]) & 0x0f) << 4 | (indexOf(acid[i+2]) & 0x3f) >> 2;
        enc[j + 2] = (indexOf(acid[i + 2]) & 0x03) << 6 | indexOf(acid[i + 3]);
        printf(" 0x%02x", enc[j]);
        printf(" 0x%02x", enc[j + 1]);
        printf(" 0x%02x\n\n", enc[j + 2]);
    }
    return 0;
}
