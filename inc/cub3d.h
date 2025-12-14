/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:36:19 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 14:38:54 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> // FIXME: remove when debug is removed
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <float.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/megalibft/libft.h"
# include "../lib/queue/queue.h"
# include "defines.h"

// --- UTILS ---
// utils/ft_error.c
int		ft_error(char *str);
// utils/math.c
float	deg_to_rads(float deg);
// utils/free_array.c
void	free_array(void **arr);

// core/init.c
int		init_structs(t_cub *cub);
void	free_all(t_cub *cub);
// core/init_player.c
void	init_player(t_player *player, char **map, int map_height);
// core/init_minimap_bonus.c
int		init_minimap(t_win *win);

// mlx/hooks.c
void	key_hook(mlx_key_data_t keydata, void *param);
// mlx/window.c
int		init_window(t_win *win);
void	safe_put_pixel(mlx_image_t	*img, int x, int y, uint32_t color);
void	clear_screen(t_cub *cub);
// rendering/draw.c
void	draw_cube(t_win *win, int x, int y, int color);
void	draw_line(t_win *win, t_point from, t_point to, uint32_t color);
void	draw_circle(t_win *win, int center_x, int center_y);
// rendering/minimap_bonus.c
int		init_minimap(t_win *win);
void	draw_minimap(t_cub *cub);
// rendering/player.c
void	rotate_player(t_player *player, double rotation);
void	player_motion(t_player *player, keys_t key, t_cub *cub);
// rendering/raycast.c
void	init_step(t_cub *cub, t_ray *ray);
void	raycast(t_cub *cub);
// rendering/texture.c
void	render_ceiling(t_cub *cub, t_ray *ray, int x);
void	render_floor(t_cub *cub, t_ray *ray, int x);
void	render_wall(t_cub *cub, t_ray *ray, int x);
// utils/init.c
bool cub_init(char *mapfile, t_cub *cub);
void cub_free(t_cub *cub);
// utils/mlx.c
mlx_image_t	*my_mlx_load_image(t_win *win, char *path);
// -------------

// --- PARSER ---
// parser/texture_utils.c
bool	set_valid_color(char *color, uint32_t *value);
// parser/index.c
bool set_texture(char ***texture, int fd);
bool set_map(t_map *map, int fd);
// --------------

// --- VALIDATOR ---
// validator/bfs_utils.c
bool **get_visited_map(size_t width, size_t height);
bool visit_point(size_t x, size_t y, t_bfs *data);
bool visit_borders(t_bfs *data);
bool visit_neighbourgs(t_point point, t_bfs *data);
bool has_invalid_spaces(t_map map, bool **visited);
// validator/bfs.c
void bfs_free(t_queue *queue, bool **visited, size_t row_count);
bool bfs(t_map map);
// validator/utils.c
bool all_valid_chars(char **map);
bool is_one_player(char **map);
bool	is_filename_valid(char *filename);
// ./main.c
bool is_map_valid(t_map map);
bool	set_valid_textures(char **texture, t_win *win);
// -----------------

#endif
