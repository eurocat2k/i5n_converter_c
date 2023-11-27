#ifndef I5N_BCC37392_3CD6_46BF_93FF_CB189DEFCAB8
#define I5N_BCC37392_3CD6_46BF_93FF_CB189DEFCAB8
#include <unistd.h>
#ifndef I5N_SIXBITS_SIZE
#define I5N_SIXBITS_SIZE 6
#endif
#ifndef I5N_ASCII_SIZE
#define I5N_ASCII_SIZE 8
#endif
#ifndef BYTE_TO_BINARY
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')
#endif
void i5n_encode(char *const dst, const char *src, size_t len);
void i5n_decode(char *const dst, const char *src, size_t len);
#endif /* I5N_BCC37392_3CD6_46BF_93FF_CB189DEFCAB8 */
