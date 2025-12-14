/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:42:50 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 19:10:03 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	init_window(t_cub *cub)
{
	cub->win->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, false);
	if (!cub->win->mlx)
		return (ERROR);
	cub->win->game = mlx_new_image(cub->win->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->win->game)
	{
		mlx_close_window(cub->win->mlx);
		return (ERROR);
	}
	if (mlx_image_to_window(cub->win->mlx, cub->win->game, 0, 0) == -1)
	{
		mlx_delete_image(cub->win->mlx, cub->win->game);
		mlx_close_window(cub->win->mlx);
		return (ERROR);
	}
	if (!set_valid_textures(cub->texture, cub->win))
	{
		mlx_delete_image(cub->win->mlx, cub->win->game);
		mlx_close_window(cub->win->mlx);
		cub_free(cub);
		return (ERROR);
	}
	init_minimap(cub->win);
	return (SUCCESS);
}

void	safe_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (!img)
		return ;
	if (x < 0 || y < 0 || x >= (int)img->width || y >= (int)img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void	clear_screen(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)cub->win->game->height)
	{
		x = 0;
		while (x < (int)cub->win->game->width)
		{
			safe_put_pixel(cub->win->game, x, y, BLACK);
			x++;
		}
		y++;
	}
	clear_mmap_window(cub);
}
