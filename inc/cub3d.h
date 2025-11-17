/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:36:19 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/17 18:08:19 by sblanco-         ###   ########.fr       */
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

// validator/validator.c
bool is_map_valid(t_map map);

#endif
