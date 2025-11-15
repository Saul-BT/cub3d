#include "../../inc/cub3d.h"

static bool all_textures_setted(char **texture)
{
    return (texture[NORTH] && texture[SOUTH] && texture[WEST] && texture[EAST] && texture[C_FLOOR] && texture[C_CEILING]);
}

bool set_texture(char ***texture, int fd)
{
    int tex_id;
    int tex_id_len;
    char *line;
    static char *texture_ids[6];
    texture_ids[NORTH] = "NO ";
	texture_ids[SOUTH] = "SO ";
	texture_ids[EAST] = "EA ";
	texture_ids[WEST] = "WE ";
	texture_ids[C_FLOOR] = "F ";
	texture_ids[C_CEILING] = "C ";

    *texture = ft_calloc(6, sizeof(char *));
    if (!*texture)
        return false;
    
    while(!all_textures_setted(*texture) && (line = get_next_line(fd)) != NULL)
    {
        if (*line == '\n')
        {
            free(line);
            continue;
        }
        tex_id = 0;
        while(tex_id < 6)
        {
            tex_id_len = ft_strlen(texture_ids[tex_id]);
            if (ft_strncmp(texture_ids[tex_id], line, tex_id_len) == 0)
            {
                if ((*texture)[tex_id]) {
                    tex_id++;
                    continue;
                }
                (*texture)[tex_id] = ft_substr(line, tex_id_len, ft_strlen(line + tex_id_len + 1));
                if (!(*texture)[tex_id]) {
                    free(line);
                    return false;
                }
                break;
            }
            tex_id++;
        }
        if (tex_id == 6)
        {
            free(line);
            return false;
        }
        free(line);
    }

    return true;
}

static char *read_map(char *head, int fd)
{
    char *line;
    char *tmp;
    char *map;

    map = head;
    tmp = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (*line == '\n')
        {
            free(map);
            free(line);
            return false;
        }
        tmp = ft_strjoin(map, line);
        free(map);
        free(line);
        if (!tmp)
            return NULL;
        map = tmp;
    }

    return map;
}

bool set_map(char ***map, int fd)
{
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