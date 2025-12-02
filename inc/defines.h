/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:13:26 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/20 20:38:24 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIN_NAME "cub3d"
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720

# define TILE 128 //a tile in the map will occupy 64x64 pixels
# define FOV 0.785398 //45º
# define MOVE_SPEED 0.25
# define ROTATION_SPEED 0.15

# define RAY_LENGTH 1 //used in the minimap

// following the Unit Circle in radians and NSEW equivalents
# define N 1.5708 //90º
# define E 0 //0º / 360º
# define S 4.71239 //270º
# define W 3.14159 //180º

# define BLUE 0x00FFFFFF
# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF

# define SUCCESS 0
# define ERROR 1

# define PI 3.141592653589

typedef struct	s_win
{
	mlx_t		*mlx;
	mlx_image_t	*mmap;
}	t_win;

typedef	struct	s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;

// main cub3d struct
typedef struct	s_cub
{
	t_win		*win;
	char		**map;
	int			map_height;
	int			map_width;
	t_player	*player;
}	t_cub;

#endif
