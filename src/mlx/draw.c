/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:15:59 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/14 21:18:19 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * function made to access the point memory slot on the display
 */
void	img_pixel_put(t_mlx *mlx, t_point p)
{
	char	*pixel_pos;
	int	offset;

	if (!(p.x >= 0 && p.x < WIN_WIDTH && p.y >= 0 && p.y < WIN_HEIGHT))
		return ;
	offset = p.y * mlx->line_length + p.x * (mlx->bpp / 8);
	pixel_pos = mlx->img_addr + offset;
	*(unsigned int *)pixel_pos = p.color;
}
