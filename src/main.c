/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:27:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/14 21:01:17 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char** get_mock_map(void)
{
	static char **map_data;

	map_data = {
		"111111",
		"100101",
		"101001",
		"1100N1",
		"111111",
		NULL
	};
	return (map_data);
}

int	main(int argc, char **argv) 
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_cub3d		cub;

	if (argc != 2)
		return (ft_error("usage: ./cub3d mapfile.cub"));

	printf("map file: %s\n", argv[1]);
	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, false);
	if (!mlx)
		return (ERROR);
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
	{
		mlx_close_window(mlx);
		return (ERROR);
	}
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		return (ERROR);
	}
	mlx_key_hook(mlx, &key_hook, mlx);
	
	cub.map = get_mock_map();

	mlx_loop(mlx);
	mlx_terminate(mlx);
	
	//free(cub.map, mlx);
	return (SUCCESS);
}
