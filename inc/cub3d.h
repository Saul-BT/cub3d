/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:36:19 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 12:18:44 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> //TODO: delete all printf calls
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/megalibft/libft.h"
# include "defines.h"

// utils/ft_error.c
int		ft_error(char *str);
// utils/math.c
float	deg_to_rads(float deg);
// utils/free_array.c
void	free_array(void **arr);

// core/init.c
int		init_structs(t_cub *cub);
void	free_all(t_cub *cub);

// mlx/hooks.c
void	key_hook(mlx_key_data_t keydata, void *param);
// mlx/window.c
int		init_window(t_win *win);
void	safe_put_pixel(mlx_image_t	*img, int x, int y, uint32_t color);
void	clear_screen(t_cub *cub);
// rendering/draw.c
void	draw_cube(t_win *win, int x, int y, int color);
void	draw_line(t_win *win, t_point from, t_point to, uint32_t color);
void	draw_grid(t_win *win);
void	draw_circle(t_win *win, int center_x, int center_y);
// rendering/minimap.c
int		init_minimap(t_win *win);
void	draw_minimap(t_cub *cub);
// rendering/player.c
int		is_player(char c);
void	init_player_position(t_player *player, char **map, int map_height);
void	rotate_player(t_player *p, double rotation);
void	player_motion(t_player *p, keys_t key, t_cub *cub);
// rendering/raycast.c
void	init_step(t_cub *cub, t_ray *ray);
void	raycast(t_cub *cub);
// rendering/texture.c
void	render_ceiling(t_cub *cub, t_ray *ray, int x);
void	render_floor(t_cub *cub, t_ray *ray, int x);
void	render_wall(t_cub *cub, t_ray *ray, int x);

#endif
