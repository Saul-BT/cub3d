#include "../../inc/cub3d.h"

static char	*ft_strndup(const char *s1, size_t tam)
{
	char	*res;

	res = (char *)malloc(tam + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, tam);
	return (res);
}

static bool set_texture(t_texture *texture, int fd)
{
    char *line = get_next_line(fd);
    if (!line) {
        return false;
    }

    while(line != NULL)
    {
        if (ft_strncmp("NO", line, 2) == 0)
        {
            if (texture->north) {
                free(line);
                return false;
            }
            texture->north = ft_strndup(line + 3, ft_strlen(line + 3));
            if (!texture->north) {
                free(line);
                return false;
            }
        }
        if (ft_strncmp("SO", line, 2) == 0)
        {
            if (texture->south) {
                free(line);
                return false;
            }
            texture->south = ft_strndup(line + 3, ft_strlen(line + 3));
            if (!texture->south) {
                free(line);
                return false;
            }
        }
        if (ft_strncmp("WE", line, 2) == 0)
        {
            if (texture->west) {
                free(line);
                return false;
            }
            texture->west = ft_strndup(line + 3, ft_strlen(line + 3));
            if (!texture->west) {
                free(line);
                return false;
            }
        }
        if (ft_strncmp("EA", line, 2) == 0)
        {
            if (texture->east) {
                free(line);
                return false;
            }
            texture->east = ft_strndup(line + 3, ft_strlen(line + 3));
            if (!texture->east) {
                free(line);
                return false;
            }
        }
        if (ft_strncmp("F", line, 1) == 0)
        {
            if (texture->color_floor) {
                free(line);
                return false;
            }
            texture->color_floor = ft_strndup(line + 2, ft_strlen(line + 2));
            if (!texture->color_floor) {
                free(line);
                return false;
            }
        }
        if (ft_strncmp("C", line, 1) == 0)
        {
            if (texture->color_ceiling) {
                free(line);
                return false;
            }
            texture->color_ceiling = ft_strndup(line + 2, ft_strlen(line + 2));
            if (!texture->color_ceiling) {
                free(line);
                return false;
            }
        }
        free(line);
        if (texture->north && texture->south && texture->west && texture->east && texture->color_floor && texture->color_ceiling)
            break;
        line = get_next_line(fd);
        if (!line) {
            return false;
        }
    }

    return true;
}

static void free_map(char **map) {
    int i = 0;
    
}

static bool set_map(char ***map, int fd)
{
    int i;
    char *line;
    char **tmp;

    i = 0;
    line = get_next_line(fd);
    if (!line)
        return false;
    if (*line != '\n')
    {
        free(line);
        return NULL;
    }

    while ((line = get_next_line(fd)) != NULL && *line == '\n')
    {
        free(line);
    }
    
    while ((line) != NULL)
    {
        tmp = realloc(*map, sizeof(char *) * (i + 2));
        if (!tmp)
        {
            free(line);
            return false;
        }
        *map = tmp;
        (*map)[i] = ft_strndup(line, ft_strlen(line));
        (*map)[i+1] = NULL;
        free(line);
        line = get_next_line(fd);
        i++;
    }
    return true;
}

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
    cub3d->texture.north = NULL;
    cub3d->texture.south = NULL;
    cub3d->texture.west = NULL;
    cub3d->texture.east = NULL;
    cub3d->texture.color_floor = NULL;
    cub3d->texture.color_ceiling = NULL;
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

    if (!set_texture(&ret->texture, fd)) // FIXME: Leaks here
    {
        free(ret);
        close(fd);
        return NULL;
    }

    if (!set_map(&ret->map, fd)) // FIXME: Leaks here
    {
        free(ret);
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
