/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:13:26 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 21:21:26 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIN_NAME "cub3d"
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define MOVE_SPEED 0.25
# define ROTATION_RADS 0.15
# define MMAP_SIZE 128 // number of rows&columns * TILE size
# define TILE 16
# define MMAP_RAY_STEP 0.05
# define DBL_EPSILON 0.1

# define BLUE 0x00FFFFFF
# define RED 0xFF0000FF
# define GREEN 0x228B22FF
# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF

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
}				t_texture_type;

typedef struct s_dpoint
{
	double	x;
	double	y;
}				t_dpoint;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_win
{
	mlx_t			*mlx;
	mlx_image_t		*mmap;
	mlx_image_t		*game;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
	mlx_texture_t	*wall_north;
	mlx_texture_t	*wall_south;
	mlx_texture_t	*wall_east;
	mlx_texture_t	*wall_west;
}				t_win;

typedef struct s_player
{
	t_dpoint	pos;
	t_dpoint	dir;
	t_dpoint	plane;
}				t_player;

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
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_map
{
	char	**raw;
	int		height;
	int		width;
}				t_map;

typedef struct s_cub
{
	t_win		*win;
	t_map		map;
	t_player	*player;
	char		**texture;
}				t_cub;

typedef struct s_bfs
{
	t_map		map;
	bool		**visited;
	t_queue		queue;
}				t_bfs;

#endif
