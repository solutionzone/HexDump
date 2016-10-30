#include <stdio.h>
#include <string.h>

#include "dump.h"


// ---------------------------------------------------------------------
// convert an input character into a a string for the 
// hex part of the output and a char for the ascii part 
// of the output if possible, or a . if the character is 
// not printable
// ---------------------------------------------------------------------
int convert_char(unsigned char src, char *hex, char *ascii)
{
	char hexchars[] = "0123456789ABCDEF";
	int result = TRUE;

	hex[0] = hexchars[(src & 0xF0) >> 4];
	hex[1] = hexchars[(src & 0x0F)];
	hex[2] = ' ';
	*ascii = (!isalnum( src)) ? '.' : (char)src;
	
	return result;
}


// --------------------------------------------------------------------------------
// Dump the source byte array as nicely formatted
// output, to the output File.  The output is like this where blocksize = 16:
// 0         1         2         3         4         5         6         7         
// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
// --------------------------------------------------------------------------------
// +oooooooo xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx *................*  
// --------| OFFSET_LENGTH
//           |-| <HEX_CHAR_DUMP_SIZE
//           |----------------------------------------------| space_for_hex
//           | hex_start
//                                                           | asc_start
//                                                                    asc_end | 
// --------------------------------------------------------------------------------
//
int dump(BYTE *src, int length, int block_size, FILE *target)
{
	
	// range check block size to avoid any unpleasantness...
	block_size = ((block_size <= MAX_BLOCK_SIZE) && (block_size > 0)) ? block_size : MAX_BLOCK_SIZE;	
	int src_offset = 0;
	char buffer[MAX_LINE];
	int space_for_hex = (block_size * HEX_CHAR_DUMP_SIZE);
  int hex_start = OFFSET_LENGTH + OFFSET_TO_HEX_GAP_SIZE;
  int asc_start = (hex_start + space_for_hex );
	int asc_end = (asc_start + block_size + 1); 

  fprintf(target, " %08X->\n", (unsigned int) src);
  while (src_offset < length)
	{
		memset(buffer, (int)SPACE, (size_t)MAX_LINE);
		int buf_offset = 0;
		int hextarget_offset = hex_start;
		int asctarget_offset = asc_start + 1;
		
		buffer[asc_start] = '*';
		buffer[asc_end] = '*';
		buffer[asc_end + 1] = '\0';

    sprintf(buffer, "+%08X", src_offset);
    buffer[OFFSET_LENGTH] = ':';
    
		// Format the output line
		while ((buf_offset < block_size) && (src_offset < length))
		{
			char ascii_out = '.';
			char hex_out[HEX_CHAR_DUMP_SIZE];
			
		  if (convert_char(src[src_offset], hex_out, &ascii_out))
			{
				//printf("%d->%d (%x, %x)\n", src_offset, buf_offset, hextarget_offset, asctarget_offset);

				int i;
				for (i = 0; i < HEX_CHAR_DUMP_SIZE; i++)
				{
					buffer[hextarget_offset++] = hex_out[i];
				}
				buffer[asctarget_offset++] = ascii_out;
				
				buf_offset++;
			}
			src_offset++;
		}
		fprintf(target, "%s\n", buffer);
	}
	
	return src_offset;
}
