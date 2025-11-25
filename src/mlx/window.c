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
	win->mmap = mlx_new_image(win->mlx, WIN_WIDTH, WIN_HEIGHT);
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
	return (SUCCESS);
}
