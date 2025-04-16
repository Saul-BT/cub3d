#include "../cub3d.h"

//falta comprobar la valided de los archivos de texto, accesibilidad 
//y que no esten reppetidos.
bool fill_texture(t_data *data, char *file, int flag)
{
	if (flag  == 'N')
	{
		data->n_texture = ft_strdup(ft_strtrim(file, " "));
		return (true);
	}
	else if (flag  == 'S')
	{
		data->s_texture = ft_strdup(ft_strtrim(file, " "));
		return (true);
	}
	else if (flag  == 'E')
	{
		data->e_texture = ft_strdup(ft_strtrim(file, " "));
		return (true);
	}
	else if (flag  == 'W')
	{
		data->w_texture = ft_strdup(ft_strtrim(file, " "));
		return (true);
	}
	return (false);
}

bool check_texture(t_data *data, char *file)
{
	if (!ft_strncmp("NO ", file, 3))
		return (fill_texture(data, file + 3, 'N'));
	else if (!ft_strncmp("SO ", file, 3))
		return (fill_texture(data, file + 3, 'S'));
	else if (!ft_strncmp("WE ", file, 3))
		return (fill_texture(data, file + 3, 'W'));
	else if (!ft_strncmp("EA ", file, 3))
		return (fill_texture(data, file + 3, 'E'));
	printf("cub3d error: No valid orientation identifier on textures\n");
	return (false);
}


//antes de hacer el split hay quue comprobar que el numero tiene formato
//valido. Una vez hecho el atoi tambien hay que ver que cumple e rango 
//[0, 255]
bool	fill_rgb(t_data *data, char *color, int flag)
{
	char	**mat;

	//comprobacion.
	mat = ft_split(ft_strtrim(color, " "), ',');
	if (flag  == 'F')
	{
		data->floor_color->red = ft_atoi(mat[0]);
		data->floor_color->green = ft_atoi(mat[1]);
		data->floor_color->blue = ft_atoi(mat[2]);
		return (true);
	}
	else if (flag  == 'C')
	{
		data->ceiling_color->red = ft_atoi(mat[0]);
		data->ceiling_color->green = ft_atoi(mat[1]);
		data->ceiling_color->blue = ft_atoi(mat[2]);
		return (true);
	}
	return (false);
}

bool check_rgb(t_data *data, char *color)
{
	if (!ft_strncmp("F ", color, 2))
		return (fill_rgb(data, color + 2, 'F'));
	else if (!ft_strncmp("C ", color, 2))
		return (fill_rgb(data, color + 2, 'C'));
	printf("cub3d error: No valid location identifier on colors\n");
	return (false);
}


//comprobaciion de que no haya espacios en blanco, solo un jugador, solo 
//caracteres validos y tras eso floodfill
bool	check_map(t_data *data, char **map)
{
	int	i;

	i = 0;
	while(map[i])
		i++;
	data->map->y_size = i;
	i = 0;
	data->map->map = malloc(sizeof(char *) * (data->map->y_size + 1));
	data->map->map[data->map->y_size] = NULL;
	while(i < data->map->y_size)
	{
		data->map->map[i] = map[i];
		i++;
	}
	return (true);
}

static bool	fill_data_struct(t_data *data, char **fixed_data)
{	
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (!check_texture(data, fixed_data[i]))
		{
			return (false);
		}
		i++;
	}
	while (i < 6)
	{
		if (!check_rgb(data, fixed_data[i]))
		{
			return (false);
		}
		i++;
	}
	if (!check_map(data, fixed_data + 6))
	{
		return (false);
	}
	return (true);
}
//asd
char	**file_to_char_convert(char *filename)
{
	char	**raw_data;
	char	**fixed_data;

	raw_data = fill_raw_data(filename);
	fixed_data = get_fixed_data(raw_data);
	// freematrix(raw_data);
	return (fixed_data);
}

bool	file_interpreter(char *filename, t_data *data)
{
	char	**fixed_data;

	fixed_data = file_to_char_convert(filename);
	if (!fill_data_struct(data, fixed_data))
		return (false);
	//liberar enn caso de que sea false;
	// freematrix(fixed_data);
	return (true);
}