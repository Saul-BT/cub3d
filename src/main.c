/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:27:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/08 18:43:19 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	debug(t_cub3d **cub3d)
{
	size_t	i;

	i = 0;
	printf("NO %s\n", (*cub3d)->texture[NORTH]);
	printf("SO %s\n", (*cub3d)->texture[SOUTH]);
	printf("WE %s\n", (*cub3d)->texture[WEST]);
	printf("EA %s\n", (*cub3d)->texture[EAST]);
	printf("\n");
	printf("F %d, %d, %d\n", (((*cub3d)->mlx.floor_color >> 24) & 0xFF),
		(((*cub3d)->mlx.floor_color >> 16) & 0xFF),
		(((*cub3d)->mlx.floor_color >> 8) & 0xFF));
	printf("C %d, %d, %d\n", (((*cub3d)->mlx.ceiling_color >> 24) & 0xFF),
		(((*cub3d)->mlx.ceiling_color >> 16) & 0xFF),
		(((*cub3d)->mlx.ceiling_color >> 8) & 0xFF));
	printf("\n");
	while ((*cub3d)->map.raw[i])
		printf("%s\n", (*cub3d)->map.raw[i++]);
	printf("\nMap size: %ld x %ld\n", (*cub3d)->map.width,
		(*cub3d)->map.height);
	free_cub3d(cub3d);
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	if (argc != 2)
		return (ft_error("usage: ./cub3d mapfile.cub"));
	cub3d = cub3d_init(argv[1]);
	if (!cub3d)
		return (ERROR);
	if (!is_map_valid(cub3d->map) || !set_valid_textures(cub3d->texture,
			&cub3d->mlx))
	{
		free_cub3d(&cub3d);
		return (ERROR);
	}
	debug(&cub3d);
	mlx_loop(cub3d->mlx.mlx);
	return (SUCCESS);
}
