#include "cub3d.h"

void	freematrix(char	**matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	free_data(t_data *data)
{
	freematrix(data->map->map);
	free(data->ceiling_color);
	free(data->floor_color);
	free(data->player);
	free(data->map);
	free(data->ceiling_color);
	return (1);
}

void	printmat(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("%s\n",matrix[i]);
		i++;
	}

}