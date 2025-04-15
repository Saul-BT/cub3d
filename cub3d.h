#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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

typedef struct	s_map
{
	char	**map;
	int		x_size;
	int		y_size;
}				t_map;

typedef struct  s_data
{
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	t_rgb_color	*ceiling_color;
	t_rgb_color	*floor_color;
	t_player	*player;
	t_map		*map;

}				t_data;

//UTILS (FREE)
int		free_data(t_data *data);
void	freematrix(char	**matrix);
//borrar
void	printmat(char **matrix);


//FILES
//check
bool	valid_file(char *filename, bool extension);
//parse
bool	file_interpreter(char *filename, t_data *data);
//raw data
char	**fill_raw_data(char *filename);
char	**get_fixed_data(char **raw_data);


#endif