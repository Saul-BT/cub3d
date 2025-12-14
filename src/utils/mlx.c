/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:37:59 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/08 18:38:00 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

mlx_image_t	*my_mlx_load_image(t_win *win, char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	return (mlx_texture_to_image(win->mlx, texture));
}
