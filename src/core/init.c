/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:10:08 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 22:26:10 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_defaults(t_cub *cub)
{
	cub->map.raw = NULL;
	cub->map.height = 0;
	cub->map.width = 0;
	cub->win.mlx = NULL;
	cub->win.mmap = NULL;
	cub->win.game = NULL;
	cub->win.wall_east = NULL;
	cub->win.wall_north = NULL;
	cub->win.wall_south = NULL;
	cub->win.wall_west = NULL;
	cub->win.ceiling_color = 0;
	cub->win.floor_color = 0;
	cub->player.dir = (t_dpoint){0, 0};
	cub->player.pos = (t_dpoint){0, 0};
	cub->player.plane = (t_dpoint){0, 0};
	cub->texture = NULL;
}

void	cub_free(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map.raw && cub->map.raw[i])
		free(cub->map.raw[i++]);
	free(cub->map.raw);
	i = 0;
	while (cub->texture && i < 6)
	{
		if (cub->texture[i])
			free(cub->texture[i]);
		i++;
	}
	free(cub->texture);
	set_defaults(cub);
}

static bool	set_mapfile_stuff(char *mapfile, t_cub *cub, int *fd)
{
	if (!is_filename_valid(mapfile))
		return (false);
	set_defaults(cub);
	*fd = open(mapfile, O_RDONLY);
	if (*fd == -1)
	{
		ft_error("error: cant read the mapfile, plz check the provided path");
		return (false);
	}
	if (!set_textures(&cub->texture, *fd))
	{
		ft_error("error: there are weird textures in the mapfile.");
		cub_free(cub);
		return (close(*fd), false);
	}
	if (!set_map(&cub->map, *fd))
	{
		ft_error("error: the map zone is broken/missing, idk.");
		cub_free(cub);
		return (close(*fd), false);
	}
	return (true);
}

bool	cub_init(char *mapfile, t_cub *cub)
{
	int	fd;

	if (!set_mapfile_stuff(mapfile, cub, &fd))
		return (false);
	if (init_window(cub) == ERROR)
	{
		cub_free(cub);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
