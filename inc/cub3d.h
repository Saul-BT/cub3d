/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:36:19 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/14 21:07:03 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> //TODO: delete all printf calls
# include <stdlib.h>
# include <math.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/megalibft/libft.h"
# include "defines.h"

// utils/ft_error.c
int     ft_error(char *str);
// utils/math.c
float	deg_to_rads(float deg);

// mlx/hooks.c
void	key_hook(mlx_key_data_t keydata, void *param);
// mlx/window.c
int		init_window(t_win *win);

// rendering/draw.c
void	clear_screen(t_cub *cub);
void	draw_cube(t_win *win, int x, int y, int color);
void	draw_minimap(t_cub *cub);
void	draw_grid(t_cub *cub, t_win *win);
// rendering/map.c
void	get_map_dimensions(char **map, t_cub *cub);
// rendering/player.c
int     is_player(char c);
void	move_player(t_cub *cub, float dx, float dy);
void	rotate_player(t_cub *cub, float rotation);
void	init_player_position(t_cub *cub);


#endif
