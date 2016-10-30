#include <stdio.h>
#include <string.h>

#include "dump.h"

// ---------------------------------------------------------------------
// Main. Test harness for seeing if the dump functions work.
// ---------------------------------------------------------------------
//
int main (int argc, char *argv[])
{
	int result = 0;
	int block_size = 16;
	unsigned char input[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
														0x08, 0x09, 0x31, 0x32, 0x45, 0x46, 0x0E, 0x0F,
														0x70, 0x65, 0x29, 0xFA, 0xAD};
	
	if (argc > 1)
	{
		block_size = atoi(argv[1]);
	}
	
	printf("Test Harness...\n");
	printf("  ...block_size = %d\n", block_size);
	result = dump(input, sizeof(input), block_size, stdout); 
	printf("Done...[%x]\n", result);
}
