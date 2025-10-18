#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "cart.h"

void usage();

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
	
	if ( (read(fd, &myHeader, sizeof(rom_header_t))) );
		else {

		perror("read()");
		exit(1);
		}

	if ( checkSignature(&myHeader) )  {

	  puts("signature OK");
	}

	else { puts("Does not appear to be a valid iNES rom"); }

	//dumpiNESHeader();

	return 0;
}

void usage()  {

	puts("point me at a iNES ROM");
	exit(1);
}
