#include "cub3d.h"
static bool	non_init_errors(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("cub3d error: Invalid number of arguments");
		return (1);
	}
	if (!valid_file(argv[1], true))
		return (1);
	return (0);
}

static t_data *init_data(void)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	data->ceiling_color = malloc(sizeof(t_rgb_color));
	data->floor_color = malloc(sizeof(t_rgb_color));
	data->player = malloc(sizeof(t_player));
	data->map = malloc(sizeof(t_map));
	if (!data || !data->ceiling_color || !data->floor_color
		|| !data->player || !data->map)
		return (NULL);
	data->n_texture = NULL;
	data->s_texture = NULL;
	data->w_texture = NULL;
	data->e_texture = NULL;
	return (data);
}

int main(int argc, char **argv)
{
	t_data *data;

	if (non_init_errors(argc, argv))
		return (1);
	data = init_data();
	if (!data)
		return (free_data(data));
	if (!file_interpreter(argv[1], data))
	{
		return (free_data(data));
	}
	printf("todo sigue ok en el main\n");
	
	return (0);
}