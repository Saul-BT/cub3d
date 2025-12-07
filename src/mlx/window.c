/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:42:50 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/25 19:42:51 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	init_window(t_win *win)
{
	win->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, false);
	if (!win->mlx)
		return (ERROR);
	//TODO: make minimap smaller and drawings scaled to that size
	win->mmap = mlx_new_image(win->mlx,
		WIN_WIDTH, WIN_HEIGHT);
	if (!win->mmap)
	{
		mlx_close_window(win->mlx);
		return (ERROR);
	}
	if (mlx_image_to_window(win->mlx, win->mmap, 0, 0) == -1)
	{
		mlx_delete_image(win->mlx, win->mmap);
		mlx_close_window(win->mlx);
		return (ERROR);
	}
	// win->game = mlx_new_image(win->mlx, WIN_WIDTH, WIN_HEIGHT);
	// if (!win->mmap)
	// {
	// 	mlx_delete_image(win->mlx, win->mmap);
	// 	mlx_close_window(win->mlx);
	// 	return (ERROR);
	// }
	// if (mlx_image_to_window(win->mlx, win->game, 0, 0) == -1)
	// {
	// 	mlx_delete_image(win->mlx, win->mmap);
	// 	mlx_delete_image(win->mlx, win->game);
	// 	mlx_close_window(win->mlx);
	// 	return (ERROR);
	// }
	return (SUCCESS);
}

void	free_window(t_win *win)
{
	//mlx_delete_image(win->mlx, win->game);
	mlx_delete_image(win->mlx, win->mmap);
	mlx_close_window(win->mlx);
}

void	safe_put_pixel(mlx_image_t	*img, int x, int y, uint32_t color)
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