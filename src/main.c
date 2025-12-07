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

int	main(int argc, char **argv) 
{
	t_cub	cub;
	int		error;

	//TODO: activate when parser is done
	//if (argc != 2)
	//	return (ft_error("usage: ./cub3d mapfile.cub"));
	//printf("map file: %s\n", argv[1]);
	(void)argc, (void)argv;

	error = init_structs(&cub);
	if (error)
		return (ERROR);
	mlx_key_hook(cub.win->mlx, &key_hook, &cub);
	get_map_dimensions(cub.map, &cub.map_width, &cub.map_height);
	init_player_position(&cub);
	draw_minimap(&cub);
	//raycast(&cub);
	mlx_loop(cub.win->mlx);
	mlx_terminate(cub.win->mlx);
	//free_struct(cub.win);
	return (SUCCESS);
}
