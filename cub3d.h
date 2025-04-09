#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <libft.h>

typedef struct	s_player
{
	int		x_pos;
	int		y_pos;
	char	orientation;
}				t_player;

typedef struct s_rgb_color
{
	int		red;
	int		green;
	int		blue;
}			t_rgb_color;

typedef struct  s_data
{
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	t_rgb_color	ceiling_color;
	t_rgb_color	floor_color;
	t_player	player;
	t_map		map;

}				t_data;

typedef struct	s_map
{
	char	**map
	int		x_size;
	int		y_size;
}				t_map;

#endif