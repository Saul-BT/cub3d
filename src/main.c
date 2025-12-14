/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:27:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 12:34:56 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_map_dimensions(char **map, int *map_width, int *map_height)
{
	int	y;
	int	x;
	int	max_x;

	if (!map)
		return ;
	max_x = 0;
	x = 0;
	y = 0;
	while (map[y])
	{
		x = ft_strlen(map[y]);
		if (x > max_x)
			max_x = x;
		y++;
	}
	*map_height = y;
	*map_width = max_x;
}

//TODO: activate parser
int	main(int argc, char **argv)
{
	t_cub	cub;
	int		error;

	(void)argc, (void)argv;
	error = init_structs(&cub);
	if (error)
		return (ERROR);
	mlx_key_hook(cub.win->mlx, &key_hook, &cub);
	get_map_dimensions(cub.map, &cub.map_width, &cub.map_height);
	init_player(cub.player, cub.map, cub.map_height);
	draw_minimap(&cub);
	raycast(&cub);
	mlx_loop(cub.win->mlx);
	free_all(&cub);
	return (SUCCESS);
}
