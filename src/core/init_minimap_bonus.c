/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:43:22 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 14:08:30 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	init_minimap(t_win *win)
{
	win->mmap = mlx_new_image(win->mlx, MMAP_SIZE, MMAP_SIZE);
	if (!win->mmap)
	{
		mlx_delete_image(win->mlx, win->game);
		mlx_close_window(win->mlx);
		return (ERROR);
	}
	if (mlx_image_to_window(win->mlx, win->mmap, WIN_WIDTH - MMAP_SIZE, 20)
		== -1)
	{
		mlx_delete_image(win->mlx, win->mmap);
		mlx_delete_image(win->mlx, win->game);
		mlx_close_window(win->mlx);
		return (ERROR);
	}
	return (SUCCESS);
}

void	clear_mmap_window(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)cub->win->mmap->height)
	{
		x = 0;
		while (x < (int)cub->win->mmap->width)
		{
			safe_put_pixel(cub->win->mmap, x, y, BLACK);
			x++;
		}
		y++;
	}
}
