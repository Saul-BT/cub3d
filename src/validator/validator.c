#include "../../inc/cub3d.h"

static bool all_valid_chars(char **map)
{
    size_t i;
    char *trimmed;

    i = 0;

    while (map[i])
    {
        trimmed = ft_strtrim(map[i], " 01NSEW");
        if (!trimmed)
            return false;
        if (ft_strlen(trimmed) > 0)
        {
            free(trimmed);
            return false;
        }
        i++;
    }

    return true;
}

/*
 111
10001
10001
10001
 111
static bool is_closed(size_t *x, size_t *y, char **map)
{
    size_t row;
    size_t col;
    size_t last_x;
    size_t last_y;

    row = y;
    col = x;
    while (map[])
}

static bool all_maps_closed(char **map)
{
    size_t x;
    size_t y;
    bool all_closed;

    y = 0;
    all_closed = true;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '0')
                all_closed = all_closed && is_cosed(x, y, map);
            x++;
        }
        y++;
    }

    return all_closed;
}
*/

bool is_map_valid(char **map)
{
    if (!all_valid_chars(map))
        return false;
    
    //if (!all_maps_closed(map))
      //  return false;

    return true;
}