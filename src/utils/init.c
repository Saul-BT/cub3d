#include "../../inc/cub3d.h"

static bool set_mlx(t_mlx *mlx)
{
    mlx->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, false);
	if (!mlx->mlx)
		return false;
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img)
	{
		mlx_close_window(mlx->mlx);
		return false;
	}
	if (mlx_image_to_window(mlx->mlx, mlx->img, 0, 0) == -1)
	{
		mlx_close_window(mlx->mlx);
		return false;
	}

    return true;
}

void set_defaults(t_cub3d *cub3d)
{
    cub3d->map = NULL;
    cub3d->mlx.img = NULL;
    cub3d->mlx.mlx = NULL;
    cub3d->texture = NULL;
}

void free_cub3d(t_cub3d **cub3d)
{
    size_t i;

    i = 0;
    while((*cub3d)->map && (*cub3d)->map[i])
        free((*cub3d)->map[i++]);
    free((*cub3d)->map);
    free((*cub3d)->mlx.img);
    free((*cub3d)->mlx.mlx);
    i = 0;
    while ((*cub3d)->texture && i < 6)
        free((*cub3d)->texture[i++]);
    free((*cub3d)->texture);
    set_defaults(*cub3d);
    free(*cub3d);
    *cub3d = NULL;
}

t_cub3d *cub3d_init(char *mapfile)
{
    int fd;
    t_cub3d *ret;

    ret = malloc(sizeof(t_cub3d));
    if (!ret)
        return NULL;

    set_defaults(ret);

    fd = open(mapfile, O_RDONLY);
    if (fd == -1)
        return NULL;

    if (!set_texture(&ret->texture, fd))
    {
        free_cub3d(&ret);
        close(fd);
        return NULL;
    }

    if (!set_map(&ret->map, fd))
    {
        
        free_cub3d(&ret);
        close(fd);
        return NULL;
    }

/*
    if (!set_mlx(&ret->mlx)) // FIXME: Leaks here
    {
        close(fd);
        return NULL;
    }
*/
    close(fd);

    return ret;
}
