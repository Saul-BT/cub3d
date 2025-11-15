#include "../../inc/cub3d.h"

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
            texture->north = ft_substr(line, 3, ft_strlen(line + 4));
            if (!texture->north) {
                free(line);
                return false;
            }
        }
        else if (ft_strncmp("SO", line, 2) == 0)
        {
            if (texture->south) {
                free(line);
                return false;
            }
            texture->south = ft_substr(line, 3, ft_strlen(line + 4));
            if (!texture->south) {
                free(line);
                return false;
            }
        }
        else if (ft_strncmp("WE", line, 2) == 0)
        {
            if (texture->west) {
                free(line);
                return false;
            }
            texture->west = ft_substr(line, 3, ft_strlen(line + 4));
            if (!texture->west) {
                free(line);
                return false;
            }
        }
        else if (ft_strncmp("EA", line, 2) == 0)
        {
            if (texture->east) {
                free(line);
                return false;
            }
            texture->east = ft_substr(line, 3, ft_strlen(line + 4));
            if (!texture->east) {
                free(line);
                return false;
            }
        }
        else if (ft_strncmp("F", line, 1) == 0)
        {
            if (texture->color_floor) {
                free(line);
                return false;
            }
            texture->color_floor = ft_substr(line, 2, ft_strlen(line + 3));
            if (!texture->color_floor) {
                free(line);
                return false;
            }
        }
        else if (ft_strncmp("C", line, 1) == 0)
        {
            if (texture->color_ceiling) {
                free(line);
                return false;
            }
            texture->color_ceiling = ft_substr(line, 2, ft_strlen(line + 3));
            if (!texture->color_ceiling) {
                free(line);
                return false;
            }
        }
        else if (*line != '\n')
        {
            free(line);
            return false;
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

static char *read_map(char *head, int fd)
{
    char *line;
    char *tmp;
    char *map;

    map = head;
    while ((line = get_next_line(fd)) != NULL)
    {
        tmp = ft_strjoin(map, line);
        free(map);
        free(line);
        if (!tmp)
        {
            free(line);
            return NULL;
        }
        map = tmp;
    }

    return map;
}

static bool set_map(char ***map, int fd)
{
    int i;
    char *line;
    char *raw_map;

    line = get_next_line(fd);
    if (!line)
        return false;
    if (*line != '\n')
    {
        free(line);
        return false;
    }

    while (line != NULL && *line == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }

    if (!line)
        return false;
    raw_map = read_map(line, fd);
    if (!raw_map)
        return false;
    *map = ft_split(raw_map, '\n');
    free(raw_map);
    if (!*map)
        return false;

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

void free_cub3d(t_cub3d **cub3d)
{
    size_t i;

    i = 0;
    while((*cub3d)->map && (*cub3d)->map[i])
        free((*cub3d)->map[i++]);
    free((*cub3d)->map);
    free((*cub3d)->mlx.img);
    free((*cub3d)->mlx.mlx);
    free((*cub3d)->texture.north);
    free((*cub3d)->texture.south);
    free((*cub3d)->texture.west);
    free((*cub3d)->texture.east);
    free((*cub3d)->texture.color_floor);
    free((*cub3d)->texture.color_ceiling);
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

    if (!set_map(&ret->map, fd)) // FIXME: Leaks here
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
