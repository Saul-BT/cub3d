#include "cub3d.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("cub3d error: Invalid number of arguments");
		return (1);
	}
	if (!valid_file(argv[1], true))
		return (1);
	printf("todo sigue ok en el main\n");
	return (0);
}