/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:10:08 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 18:31:52 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_defaults(t_cub *cub)
{
	cub->map.raw = NULL;
	cub->map.height = 0;
	cub->map.width = 0;
	/*cub->win->game = NULL;
	cub->win->mlx = NULL;
	cub->win->wall_north = NULL;
	cub->win->wall_south = NULL;
	cub->win->wall_east = NULL;
	cub->win->wall_west = NULL;
	cub->win->floor_color = 0;
	cub->win->ceiling_color = 0;*/
	cub->texture = NULL;
}

void	cub_free(t_cub *cub)
{
	size_t	i;

	i = 0;
	while (cub->map.raw && cub->map.raw[i])
		free(cub->map.raw[i++]);
	// mlx_terminate((*cub)->win->mlx); <- check
	free(cub->map.raw);
	free(cub->win->game);
	free(cub->win->mlx);
	free(cub->win->wall_north);
	free(cub->win->wall_south);
	free(cub->win->wall_east);
	free(cub->win->wall_west);
	free(cub->win); // <- check if pointer is needed
	free(cub->player);
	// free_array(cub->map); //TODO: enable when parser is integrated
	i = 0;
	while (cub->texture && i < 6)
		free(cub->texture[i++]);
	free(cub->texture);
	set_defaults(cub);
	// free(*cub);
	//*cub = NULL;
}

bool	cub_init(char *mapfile, t_cub *cub)
{
	int fd;

	if (!is_filename_valid(mapfile))
		return (false);
	set_defaults(cub);
	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (!set_texture(&cub->texture, fd))
	{
		cub_free(cub);
		close(fd);
		return (NULL);
	}
	if (!set_map(&cub->map, fd))
	{
		cub_free(cub);
		close(fd);
		return (NULL);
	}
	// from gabri
	cub->win = malloc(sizeof(t_win));
	if (!cub->win)
		return (ft_error("malloc error in window struct\n"), NULL);
	// end of gabri
	if (init_window(cub->win) == ERROR)
	{
		cub_free(cub);
		close(fd);
		return (NULL);
	}
	close(fd);

	// from gabri
	// TODO: malloc check for map when parser is integrated
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
	{
		// free_array(ret->map); //TODO: enable when parser is integrated
		free(cub->win);
		return (ft_error("malloc error in player struct\n"), NULL);
	}
	// end of gabri

	return (cub);
}