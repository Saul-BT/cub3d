/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:13:26 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 12:17:53 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIN_NAME "cub3d"
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define MOVE_SPEED 0.25
# define ROTATION_SPEED 0.15
# define MMAP_SIZE 128 //number of rows&columns * TILE size
# define TILE 16

# define BLUE 0x00FFFFFF
# define RED 0xFF0000FF
# define GREEN 0x228B22FF
# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF

//TODO: delete when merged with parser
# define WALL_NORTH "./assets/textures/minecraft/creeper.png"
# define WALL_SOUTH "./assets/textures/minecraft/enderman.png"
# define WALL_EAST "./assets/textures/minecraft/pig.png"
# define WALL_WEST "./assets/textures/minecraft/steve.png"

# define SUCCESS 0
# define ERROR 1

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_win
{
	mlx_t			*mlx;
	mlx_image_t		*mmap; //TODO: bonus
	mlx_image_t		*game;
	mlx_texture_t	*ceiling; //TODO: bonus
	mlx_texture_t	*floor; //TODO: bonus
	uint32_t		ceiling_color;
	uint32_t		floor_color;
	mlx_texture_t	*wall_north;
	mlx_texture_t	*wall_south;
	mlx_texture_t	*wall_east;
	mlx_texture_t	*wall_west;
}	t_win;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_player;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;			//0 if wall is N,S / 1 if wall is W,E
	int			line_height;	//wall size to draw
	int			draw_start;
	int			draw_end;
}	t_ray;

typedef struct s_cub
{
	t_win		*win;
	char		**map;
	int			map_height;
	int			map_width;
	t_player	*player;
}	t_cub;

#endif
