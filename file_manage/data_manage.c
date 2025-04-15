#include "../cub3d.h"

// void	fill_data_struct(t_data *data, char **fixed_data)
// {
// 	fill_textures(data, fixed_data);
// }

char	**file_to_char_convert(char *filename)
{
	char	**raw_data;
	char	**fixed_data;

	raw_data = fill_raw_data(filename);
	fixed_data = get_fixed_data(raw_data);
	freematrix(raw_data);
	printmat(fixed_data);
	return (fixed_data);
}

bool	file_interpreter(char *filename, t_data *data)
{
	char	**fixed_data;
	(void)data;
	fixed_data = file_to_char_convert(filename);
	// fill_data_struct(data, fixed_data);
	freematrix(fixed_data);
	return (true);
}