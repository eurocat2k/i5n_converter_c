#include <stdio.h>
#include <unistd.h>
#include "i5n.h"

int main() {
    // 5d a6 b1 e3 48 20
    // char callsign[] = "WZZ184  ";
    // char callsign[] = "AUA7BZ3 ";
    // char callsign[] = "MAH610  ";
    char callsign[] = "QTR41U  ";
    char encoded[I5N_SIXBITS_SIZE] = { 0 };
    char decoded[I5N_ASCII_SIZE] = { 0 };
    i5n_encode(encoded, callsign, (size_t)I5N_ASCII_SIZE);
    printf("callsign: %.*s\n", (int)(sizeof(callsign) / sizeof(callsign[0])), callsign);
    printf("encoded: [");
    for (int i = 0; i < I5N_SIXBITS_SIZE; i += 1) {
        if (i == 0)
            printf("0x%02x", (unsigned char)encoded[i]);
        else
          printf(" 0x%02x", (unsigned char)encoded[i]);
    }
    printf("]\n");
    i5n_decode(decoded, encoded, (size_t)I5N_SIXBITS_SIZE);
    printf("decoded: [");
    for (int i = 0; i < I5N_ASCII_SIZE; i += 1) {
        printf("%c", decoded[i]);
    }
    printf("]\n");
    return 0;
}
