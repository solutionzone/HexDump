#define BYTE unsigned char
#define MAX_LINE   (80)
#define OFFSET_LENGTH (9)
#define TRUE (1)
#define FALSE (0)
#define HEX_CHAR_DUMP_SIZE (3)
#define OFFSET_TO_HEX_GAP_SIZE (2)
#define MAX_BLOCK_SIZE (16)
#define SPACE (0x20)

// ---------------------------------------------------------------------
// Dump the source byte array as nicely formatted
// output, to the output File.
// ---------------------------------------------------------------------
//
int dump(BYTE *src, int length, int block_size, FILE *target);