#include "../../inc/cub3d.h"

bool is_map_valid(t_map map)
{
    if (!all_valid_chars(map.raw))
        return false;

    if (!is_one_player(map.raw))
        return false;
    
    if (!bfs(map))
        return false;

    return true;
}