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
        free(trimmed);
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
    printf("\e[1;1H\e[2J");
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
    usleep(1500);
}

static void free_bfs_stuff(t_queue *queue, bool **visited, size_t row_count)
{
    t_point *point;
    size_t row;

    row = 0;
    while (row < row_count)
    {
        free(visited[row]);
        row++;
    }
    free(visited);
    if (!queue)
        return;
    point = ft_dequeue(queue);
    while(point != NULL)
    {
        free(point);
        point = ft_dequeue(queue);
    }
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
            free_bfs_stuff(NULL, visited, y);
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
        if (ft_strchr("0NSEW", map.raw[0][x])
            || ft_strchr("0NSEW", map.raw[map.height - 1][x]))
        {
            free_bfs_stuff(&queue, visited, map.height);
            return false;
        }

        if (map.raw[0][x] != '1' && !visited[0][x])
        {
            point = malloc(sizeof(t_point));
            if (!point)
            {
                free_bfs_stuff(&queue, visited, map.height);
                return false;
            }
            point->x = x;
            point->y = 0;
            ft_enqueue(&queue, point);
            visited[0][x] = true;
        }
        if (map.raw[map.height - 1][x] != '1' && !visited[map.height - 1][x])
        {
            point = malloc(sizeof(t_point));
            if (!point)
            {
                free_bfs_stuff(&queue, visited, map.height);
                return false;
            }
            point->x = x;
            point->y = map.height - 1;
            ft_enqueue(&queue, point);
            visited[map.height - 1][x] = true;
        }
        x++;
    }
    // add points of left and right
    y = 0;
    while (y < map.height)
    {
        if (ft_strchr("0NSEW", map.raw[y][0])
            || ft_strchr("0NSEW", map.raw[y][map.width - 1]))
        {
            free_bfs_stuff(&queue, visited, map.height);
            return false;
        }

        if (map.raw[y][0] != '1' && !visited[y][0])
        {
            point = malloc(sizeof(t_point));
            if (!point)
            {
                free_bfs_stuff(&queue, visited, map.height);
                return false;
            }
            point->x = 0;
            point->y = y;
            ft_enqueue(&queue, point);
            visited[y][0] = true;
        }
        if (map.raw[y][map.width - 1] != '1' && !visited[y][map.width - 1])
        {
            point = malloc(sizeof(t_point));
            if (!point)
            {
                free_bfs_stuff(&queue, visited, map.height);
                return false;
            }
            point->x = map.width - 1;
            point->y = y;
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
            free_bfs_stuff(&queue, visited, map.height);
            return false;
        }
        
        if (ft_strchr("0NSEW", map.raw[point->y][point->x]))
        {
            free(point);
            free_bfs_stuff(&queue, visited, map.height);
            return false;
        }

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
                    free(point);
                    free_bfs_stuff(&queue, visited, map.height);
                    return false;
                }
                new_point->x = x;
                new_point->y = y;
                ft_enqueue(&queue, new_point);
                visited[y][x] = true;
            }
            i++;
        }
        free(point);
    }

    // the closed maps should have floor
    y = 0;
    while (y < map.height)
    {
        x = 0;
        while (x < map.width)
        {
            if (map.raw[y][x] == ' ' && !visited[y][x])
            {
                free_bfs_stuff(&queue, visited, map.height);
                return false;
            }
            x++;
        }
        y++;
    }

    free_bfs_stuff(&queue, visited, map.height);

    return true;
}

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