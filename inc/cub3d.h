/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:36:19 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/08 11:41:30 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> //TODO: delete all printf calls
# include <stdlib.h>
# include <fcntl.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/megalibft/libft.h"
# include "../lib/queue/queue.h"
# include "defines.h"

// utils/ft_error.c
int	ft_error(char *str);

// utils/init.c
t_cub3d *cub3d_init(char *mapfile);
void free_cub3d(t_cub3d **cub3d);

// parser/parser.c
bool set_texture(char ***texture, int fd);
bool set_map(t_map *map, int fd);

// --- VALIDATOR ---
// bfs/utils.c
bool **get_visited_map(size_t width, size_t height);
bool visit_point(size_t x, size_t y, t_bfs *data);
bool visit_borders(t_bfs *data);
bool visit_neighbourgs(t_point point, t_bfs *data);
bool has_invalid_spaces(t_map map, bool **visited);
// bfs/main.c
void bfs_free(t_queue *queue, bool **visited, size_t row_count);
bool bfs(t_map map);
// ./utils.c
bool all_valid_chars(char **map);
bool is_one_player(char **map);
// ./main.c
bool is_map_valid(t_map map);
// -----------------

#endif
