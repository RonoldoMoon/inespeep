#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint8_t ines_sig[4] = { 'N', 'E', 'S', 0x1A };

/* iNES header */
typedef struct rom_header_s  {

	uint8_t  signature[4]; //should be "NES^Z"
	uint8_t  prg_banks; //number of 16kB prgROM banks.
	uint8_t  chr_banks; //number of  8kB chrROM banks.
	uint8_t  control_1; //
	uint8_t  control_2;
	uint8_t  ram_size;  //ram size in 8kB units.
	uint8_t  unknown;
	uint8_t  reserved[6]; //set to zero.
/*
 * **control byte 1**
 * bit0 - 1 for verticle mirroring 0 for horizontal mirroring.
 * bit1 - 1 for battery backed ram at $6000-$71FF
 * bit2 - 1 for 512 byte trainer at $7000-$71FF
 * bit3 - 1 for a four screen VRAM layout
 * bit4-7 - Four lower bits for ROM mapper type.
 */
} __attribute__((packed)) rom_header_t;

int checkSignature(rom_header_t *p)  {

	unsigned char *temp = malloc(6);
	int i = 0;
	
	if (!temp)  {

		perror("malloc()");
		exit(1);
	}

	for (; i < 4; i++ )  {

		temp[i] = p->signature[i];
	}

	temp[i] = 0;

	if ( !(strcmp(temp, ines_sig)) ) { free(temp); return 1; }

	free(temp);
	return 0;
}
