/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:15:52 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/08 18:45:44 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	**get_visited_map(size_t width, size_t height)
{
	size_t	x;
	size_t	y;
	bool	**visited;

	visited = malloc(height * sizeof(bool *));
	if (!visited)
		return (NULL);
	y = 0;
	while (y < height)
	{
		x = 0;
		visited[y] = malloc(width * sizeof(bool));
		if (!visited[y])
		{
			bfs_free(NULL, visited, y);
			return (false);
		}
		while (x < width)
		{
			visited[y][x] = false;
			x++;
		}
		y++;
	}
	return (visited);
}

bool	visit_point(size_t x, size_t y, t_bfs *data)
{
	t_point	*point;

	if (data->map.raw[y][x] == '1' || data->visited[y][x])
		return (true);
	point = malloc(sizeof(t_point));
	if (!point)
		return (false);
	point->x = x;
	point->y = y;
	ft_enqueue(&(data->queue), point);
	data->visited[y][x] = true;
	return (true);
}

bool	visit_borders(t_bfs *data)
{
	size_t	i;

	i = 0;
	while (i < data->map.width)
	{
		if (ft_strchr("0NSEW", data->map.raw[0][i]) || ft_strchr("0NSEW",
				data->map.raw[data->map.height - 1][i]))
			return (false);
		if (!visit_point(i, 0, data) || !visit_point(i, data->map.height - 1,
				data))
			return (false);
		i++;
	}
	i = 0;
	while (i < data->map.height)
	{
		if (ft_strchr("0NSEW", data->map.raw[i][0]) || ft_strchr("0NSEW",
				data->map.raw[i][data->map.width - 1]))
			return (false);
		if (!visit_point(0, i, data) || !visit_point(data->map.width - 1, i,
				data))
			return (false);
		i++;
	}
	return (true);
}

bool	visit_neighbourgs(t_point point, t_bfs *data)
{
	int				i;
	size_t			x;
	size_t			y;
	t_point			*new_point;
	static t_point	directions[4];

	directions[0] = (t_point){.x = 1, .y = 0};
	directions[1] = (t_point){.x = 0, .y = 1};
	directions[2] = (t_point){.x = -1, .y = 0};
	directions[3] = (t_point){.x = 0, .y = -1};
	i = 0;
	while (i < 4)
	{
		x = point.x + directions[i].x;
		y = point.y + directions[i].y;
		if (x > 0 && x < data->map.width && y > 0 && y < data->map.height
			&& !visit_point(x, y, data))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	has_invalid_spaces(t_map map, bool **visited)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.raw[y][x] == ' ' && !visited[y][x])
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}
