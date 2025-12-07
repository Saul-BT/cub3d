/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:27:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/07 19:05:15 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void debug(t_cub3d **cub3d)
{
    printf("NO %s\n", (*cub3d)->texture[NORTH]);
    printf("SO %s\n", (*cub3d)->texture[SOUTH]);
    printf("WE %s\n", (*cub3d)->texture[WEST]);
    printf("EA %s\n", (*cub3d)->texture[EAST]);
    printf("\n");
    printf("F %s\n", (*cub3d)->texture[C_FLOOR]);
    printf("C %s\n", (*cub3d)->texture[C_CEILING]);
    printf("\n");
    for (int i = 0; (*cub3d)->map.raw[i]; i++)
        printf("%s\n", (*cub3d)->map.raw[i]);

    printf("\nMap size: %ld x %ld\n", (*cub3d)->map.width, (*cub3d)->map.height);

    free_cub3d(cub3d);
}

int	main(int argc, char **argv) 
{
	t_cub3d *cub3d;

	if (argc != 2)
		return (ft_error("usage: ./cub3d mapfile.cub"));

	cub3d = cub3d_init(argv[1]);

	if (!cub3d)
		return (ERROR);

    if (!is_map_valid(cub3d->map)){
        free_cub3d(&cub3d);
        return (ERROR);
	}
	debug(&cub3d);
//	mlx_loop(cub3d->mlx.mlx);
	return (SUCCESS);
}


