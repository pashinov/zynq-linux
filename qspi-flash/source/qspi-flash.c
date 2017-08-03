#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <fcntl.h>

#define BLK_SIZE 65536

int main(int argc, char *argv[])
{
	int i, ind = 0;
	int fd, tfd;
	unsigned int size = 0, u, addr;
	char blk[BLK_SIZE];
	if (argc == 1)
	{
		printf("Usage: %s [<input file> <address offset>] [...] -o <output file> <size>\n", argv[0]);
		printf("Example: %s file0 0x00000000 file2 0x001000 -o file3 0x10000000\n", argv[0]);
		return 0;
	}
	for (i = 1; i < argc; i++)
	{
		if (!strcmp("-o", argv[i]))
		{
			ind = i;
			break;
		}
	}
	if (!ind)
		return -1;
	fd = open(argv[ind+1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("Open error");
		return -1;
	}
	sscanf(argv[ind+2], "%x", &size);
	
	lseek(fd, 0, SEEK_SET);
	memset(blk, 0, sizeof(blk));
	for (u = 0; u < size; u+=sizeof(blk))
		write(fd, blk, sizeof(blk));
	for (i = 1; i < ind; i+=2)
	{
		tfd = open(argv[i], O_RDONLY);
		if (tfd == -1)
		{
			perror("Open error");
			return -1;
		}
		sscanf(argv[i+1], "%x", &addr);
		lseek(fd, addr, SEEK_SET);
		while((size = read(tfd, blk, sizeof(blk))) > 0)
			write(fd, blk, size);
		close(tfd);
	}
	close(fd);
	return 0;
}


















