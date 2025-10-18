#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "cart.h"

void usage();
void infoDump(rom_header_t *p);

int main(int argc, char* argv[])  {

	rom_header_t myHeader;
	int fd;

	if ( argc < 2 ) usage();

	//open file.
	if ( (fd = open(argv[1], O_RDONLY)) );
	                else {

			perror("open()");
			exit(1);
			}
	
	//read the header of file into ram
	if ( (read(fd, &myHeader, sizeof(rom_header_t))) );
		else {

		perror("read()");
		exit(1);
		}

	//check signature duh!
	if ( checkSignature(&myHeader) )  {

	  puts("signature OK");
	}

	else { puts("Does not appear to be a valid iNES rom"); }

	//dump header info to terminal.
	putchar(10);
	infoDump(&myHeader);

	return 0;
}

void usage()  {

	puts("point me at a iNES ROM");
	exit(1);
}

void infoDump(rom_header_t *p)  {

	printf("number of 16kB program rom banks   - %d\n", p->prg_banks);
	printf("number of  8kB character rom banks - %d\n", p->chr_banks);
	printf("ram size                           - %dkB\n", p->ram_size*8);
	printf("---\n");

	if ( p->control_1 & 0x01 )  printf("verticle mirroring\n");
	else printf("horizontle mirroring\n");

	if ( p->control_1 & 0x02 )  printf("battery backed ram\n");
	else printf("no battery backed ram\n");

	if ( p->control_1 & 0x04 )  printf("trainer present\n");
	else printf("no trainer present\n");

	if ( p->control_1 & 0x08 )  printf("four screen VRAM layout\n");
	else printf("not four screen VRAM layout\n");

	/*
	 * needs to look at other control byte, and dump mapper type.
	 */

}

