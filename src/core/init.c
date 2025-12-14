/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:10:08 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 20:27:06 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_defaults(t_cub *cub)
{
	cub->map.raw = NULL;
	cub->map.height = 0;
	cub->map.width = 0;
	cub->win = NULL;
	cub->player = NULL;
	cub->texture = NULL;
}

void	cub_free(t_cub *cub)
{
	size_t	i;

	i = 0;
	while (cub->map.raw && cub->map.raw[i])
		free(cub->map.raw[i++]);
	free(cub->map.raw);
	free(cub->win);
	free(cub->player);
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
	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
	{
		ft_error("error: cant read the mapfile, plz check the provided path");
		return (false);
	}
	if (!set_texture(&cub->texture, fd))
	{
		ft_error("error: there are missing textures in the mapfile.");
		cub_free(cub);
		return (close(fd), false);
	}
	if (!set_map(&cub->map, fd))
	{
		ft_error("error: the map zone is broken/missing, idk.");
		cub_free(cub);
		return (close(fd), false);
	}
	return (true);
}

bool	cub_init(char *mapfile, t_cub *cub)
{
	int	fd;

	set_mapfile_stuff(mapfile, cub, &fd);
	cub->win = malloc(sizeof(t_win));
	if (!cub->win)
		return (ft_error("malloc error in window struct\n"), NULL);
	if (init_window(cub) == ERROR)
	{
		cub_free(cub);
		close(fd);
		return (false);
	}
	close(fd);
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (cub_free(cub), ft_error("malloc error player struct\n"), NULL);
	return (true);
}
