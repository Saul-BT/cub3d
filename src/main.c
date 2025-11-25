/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:27:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/20 20:43:01 by gade-oli         ###   ########.fr       */
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

int	main(int argc, char **argv) 
{
	t_cub	cub;

	//TODO: activate when parser is done
	//if (argc != 2)
	//	return (ft_error("usage: ./cub3d mapfile.cub"));
	//printf("map file: %s\n", argv[1]);
	(void)argc, (void)argv;

	cub.win = malloc(sizeof(t_win));
	if (!cub.win)
		return (ft_error("malloc error\n"));
	if (init_window(cub.win) == ERROR)
		return (ERROR);
	//TODO: change it to real parser
	cub.map = get_mock_map();
	cub.player = malloc(sizeof(t_player));
	if (!cub.player)
	{
		//free(cub.win); TODO: create a final cleaner
		cub.player->x = 0.0;
    	cub.player->y = 0.0;
    	cub.player->angle = 0.0;
		return (ft_error("malloc error\n"));
	}
	cub.player->angle = 0.0;
	
	mlx_key_hook(cub.win->mlx, &key_hook, &cub);

	//draw_cube(cub.win, 10, 10, BLUE);
	//get_map_dimensions(cub.map, &cub);
	init_player_position(&cub);
	draw_minimap(&cub);
	printf("map dimensions: x = %d, y = %d\n", cub.map_width, cub.map_height);

	mlx_loop(cub.win->mlx);
	mlx_terminate(cub.win->mlx);
	
	//free_struct(cub.win);
	return (SUCCESS);
}
