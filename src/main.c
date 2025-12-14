/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:27:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 22:24:50 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (ft_error("usage: ./cub3d mapfile.cub"));
	if (!cub_init(argv[1], &cub))
		return (ERROR);
	if (!is_map_valid(cub.map))
	{
		cub_free(&cub);
		return (ERROR);
	}
	mlx_key_hook(cub.win.mlx, &key_hook, &cub);
	init_player(&cub.player, cub.map.raw, cub.map.height);
	draw_minimap(&cub);
	raycast(&cub);
	mlx_loop(cub.win.mlx);
	cub_free(&cub);
	return (SUCCESS);
}
