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

bool is_map_valid(char **map)
{
    if (!all_valid_chars(map))
        return false;
    

    return true;
}