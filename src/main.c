/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:27:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/19 20:19:39 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//TODO: delete when parser integrated
static char** get_mock_map(void)
{
	static char *map_data[] = {
		"111111",
		"100101",
		"101001",
		"1100N1",
		"111111",
		NULL
	};
	return (map_data);
}

//atm for 2D minimap
void	get_map_dimensions(t_cub *cub)
{
	int	y;
	int	x;
	int	max_x;

	if (!cub->map)
		return ;
	max_x = 0;
	while (cub->map[y])
	{
		x = ft_strlen(cub->map[x]);
		if (x > max_x)
			max_x = x;
		y++;
	}
	cub->map_height = y;
	cub->map_width = x;
}

/*void	draw_minimap(t_cub *cub)
{
	
}*/

// the size of a cube is atm determined through the TILE size on defines.h
void	draw_cube(t_win *win, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < TILE)
	{
		i = 0;
		while (i < TILE)
		{
			mlx_put_pixel(win->mmap, x+i, y+j, color);
			i++;
		}
		j++;
	}
}

int	init_window(t_win *win)
{
	win->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, false);
	if (!win->mlx)
		return (ERROR);
	win->mmap = mlx_new_image(win->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!win->mmap)
	{
		mlx_close_window(win->mlx);
		return (ERROR);
	}
	if (mlx_image_to_window(win->mlx, win->mmap, 0, 0) == -1)
	{
		mlx_delete_image(win->mlx, win->mmap);
		mlx_close_window(win->mlx);
		return (ERROR);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv) 
{
	t_cub	cub;

	if (argc != 2)
		return (ft_error("usage: ./cub3d mapfile.cub"));

	printf("map file: %s\n", argv[1]);
	cub.win = malloc(sizeof(t_win));
	if (!cub.win)
		return (ft_error("malloc error\n"));
	if (init_window(cub.win) == ERROR)
		return (ERROR);
	//TODO: change it to real parser
	cub.map = get_mock_map();
	
	mlx_key_hook(cub.win->mlx, &key_hook, cub.win->mlx);

	draw_cube(cub.win, 10, 10, BLUE);

	mlx_loop(cub.win->mlx);
	mlx_terminate(cub.win->mlx);
	
	//free_struct(cub.win);
	return (SUCCESS);
}
