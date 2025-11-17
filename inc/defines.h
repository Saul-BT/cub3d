/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:13:26 by gade-oli          #+#    #+#             */
/*   Updated: 2025/10/22 21:35:43 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIN_NAME "cub3d"
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720

# define SUCCESS 0
# define ERROR 1

typedef enum e_texture_type
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
	C_FLOOR = 4,
	C_CEILING = 5,
} t_texture_type;

typedef struct	s_mlx
{
	void	*img;
	void	*mlx;
}	t_mlx;

typedef struct	s_map
{
	char **raw;
	size_t	height;
	size_t	width;
}	t_map;

typedef struct	s_cub3d
{
	t_mlx mlx;
	//char	**map;
	t_map	map;
	char	**texture;
}	t_cub3d;

#endif
