
#include "../cub3d.h"

static bool is_folder(char *filename)
{
	int	fd;

	fd = open(filename, O_DIRECTORY);
	if (fd == -1)
		return (false);
	close (fd);
	return (true);
}

static bool	has_read_permission(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (false);
	close (fd);
	return (true);
}

bool	right_extension(char *filename)
{
	size_t len;

	if (!filename || !*filename)
		return (false);
	len = ft_strlen(filename);
	if (filename[--len] == 'b' && filename[--len] == 'u'
		&& filename[--len] == 'c' && filename[--len] == '.')
		return (true);
	return (false);
}

//"bool extension" comprueba que el archivo acabe en .cub para (a priori)
//utilizar esta funcion tanto para los archivos de texturas como para los
//arg del programa.

bool	valid_file(char *filename, bool extension)
{
	if (!has_read_permission(filename))
	{
		perror("cub3d error");
		return (false);
	}
	else if (is_folder(filename))
	{
		printf("cub3d error: given file is a directory\n");
		return (false);
	}

	if (extension && !right_extension(filename))
	{
		printf("cub3d error: given file has wrong extension (.cub)\n");
		return (false);
	}
	printf("todo bien\n");
	return (true);
}