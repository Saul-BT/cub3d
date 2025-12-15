/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:42:50 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/15 20:05:12 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	init_window(t_cub *cub)
{
	if (!set_valid_textures(cub->texture, &cub->win))
		return (ft_error("malformed textures."));
	cub->win.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, false);
	if (!cub->win.mlx)
		return (ft_error("window creation."));
	cub->win.game = mlx_new_image(cub->win.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->win.game)
		return (ft_error("game image creation."));
	if (mlx_image_to_window(cub->win.mlx, cub->win.game, 0, 0) == -1)
		return (ft_error("game image creation."));
	if (init_minimap(&cub->win) == ERROR)
		return (ft_error("minimap creation."));
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
	while (y < (int)cub->win.game->height)
	{
		x = 0;
		while (x < (int)cub->win.game->width)
		{
			safe_put_pixel(cub->win.game, x, y, BLACK);
			x++;
		}
		y++;
	}
	clear_mmap_window(cub);
}
