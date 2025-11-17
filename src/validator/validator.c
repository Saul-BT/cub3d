#include "../../inc/cub3d.h"

static bool all_valid_chars(char **map)
{
    size_t y;
    char *trimmed;

    y = 0;

    while (map[y])
    {
        trimmed = ft_strtrim(map[y], " 01NSEW");
        if (!trimmed)
            return false;
        if (ft_strlen(trimmed) > 0)
        {
            free(trimmed);
            return false;
        }
        y++;
    }

    return true;
}

static bool is_one_player(char **map)
{
    size_t x;
    size_t y;
    bool has_player;

    y = 0;
    has_player = false;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (ft_strchr("NSEW", map[y][x]))
            {
                if (has_player)
                    return false;
                has_player = true;
            }
            x++;
        }
        y++;
    }

    return has_player;
}

static void debug_bfs(t_map map, bool **visited)
{
    size_t x;
    size_t y;
    
    y = 0;
    printf("======================================\n");
    while (y < map.height)
    {
        x = 0;
        while (x < map.width)
        {
            if (visited[y][x])
                printf("·");
            else
                printf("%c", map.raw[y][x]);
            x++;
        }
        printf("\n");
        y++;
    }
    printf("======================================\n");
}

static bool bfs(t_map map)
{
    size_t x;
    size_t y;
    bool **visited;
    t_queue queue;
    t_point *point;

    visited = malloc(map.height * sizeof(bool *));
    if (!visited)
        return false;
    y = 0;
    while(y < map.height)
    {
        x = 0;
        visited[y] = malloc(map.width * sizeof(bool));
        if (!visited[y])
        {
            // FIXME: leak here
            return false;
        }
        while(x < map.width)
        {
            visited[y][x] = false;
            x++;
        }
        y++;
    }

    ft_queue_init(&queue);
    // add points of top and bottom
    x = 0;
    while (x < map.width)
    {
        if (ft_strchr("0NSEW", map.raw[0][x]))
        {
            // FIXME: leak here
            return false;
        }
        if (ft_strchr("0NSEW", map.raw[map.height - 1][x]))
        {
            // FIXME: leak here
            return false;
        }

        if (map.raw[0][x] != '1' && !visited[0][x])
        {
            point = malloc(sizeof(t_point));
            if (!point)
            {
                // FIXME: leak here
                return false;
            }
            ft_enqueue(&queue, point);
            visited[0][x] = true;
        }
        if (map.raw[map.height - 1][x] != '1' && !visited[map.height - 1][x])
        {
            point = malloc(sizeof(t_point));
            if (!point)
            {
                // FIXME: leak here
                return false;
            }
            ft_enqueue(&queue, point);
            visited[map.height - 1][x] = true;
        }
        x++;
    }
    // add points of left and right
    y = 0;
    while (y < map.height)
    {
        if (ft_strchr("0NSEW", map.raw[y][0]))
        {
            // FIXME: leak here
            return false;
        }
        if (ft_strchr("0NSEW", map.raw[y][map.width - 1]))
        {
            // FIXME: leak here
            return false;
        }

        if (map.raw[y][0] != '1' && !visited[y][0])
        {
            point = malloc(sizeof(t_point));
            if (!point)
            {
                // FIXME: leak here
                return false;
            }
            ft_enqueue(&queue, point);
            visited[y][0] = true;
        }
        if (map.raw[y][map.width - 1] != '1' && !visited[y][map.width - 1])
        {
            point = malloc(sizeof(t_point));
            if (!point)
            {
                // FIXME: leak here
                return false;
            }
            ft_enqueue(&queue, point);
            visited[y][map.width - 1] = true;
        }
        y++;
    }

    // actual bfs
    static t_point directions[4];
    directions[0] = (t_point){ .x = 1, .y = 0 };
    directions[1] = (t_point){ .x = 0, .y = 1 };
    directions[2] = (t_point){ .x = -1, .y = 0 };
    directions[3] = (t_point){ .x = 0, .y = -1 };

    int i;
    t_point *new_point;
    while (queue.front)
    {
        debug_bfs(map, visited);
        point = (t_point *)ft_dequeue(&queue);
        if (!point) // TODO: check if necessary
        {
            // FIXME: leak here
            return false;
        }
        
        if (ft_strchr("0NSEW", map.raw[point->y][point->x]))
        {
            // FIXME: leak here
            return false;
        }

        //free(point);
        i = 0;
        while (i < 4)
        {
            x = point->x + directions[i].x;
            y = point->y + directions[i].y;
            if (x > 0 && x < map.width && y > 0 && y < map.height
                && !visited[y][x] && map.raw[y][x] != '1')
            {
                new_point = malloc(sizeof(t_point));
                if (!new_point)
                {
                    // FIXME: leak here
                    return false;
                }
                new_point->x = x;
                new_point->y = y;
                ft_enqueue(&queue, new_point);
                visited[y][x] = true;
            }
            i++;
        }
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

bool is_map_valid(t_map map)
{
    if (!all_valid_chars(map.raw))
        return false;

    if (!is_one_player(map.raw))
        return false;
    
    if (!bfs(map))
        return false;

    //if (!all_maps_closed(map))
      //  return false;

    return true;
}