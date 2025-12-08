/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:15:55 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/08 18:45:51 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	bfs_init(t_bfs *data, t_map map)
{
	data->map = map;
	data->visited = get_visited_map(map.width, map.height);
	if (!data->visited)
		return (false);
	ft_queue_init(&(data->queue));
	if (!visit_borders(data))
	{
		bfs_free(&(data->queue), data->visited, data->map.height);
		return (false);
	}
	return (true);
}

void	bfs_free(t_queue *queue, bool **visited, size_t row_count)
{
	t_point	*point;
	size_t	row;

	row = 0;
	while (row < row_count)
	{
		free(visited[row]);
		row++;
	}
	free(visited);
	if (!queue)
		return ;
	point = ft_dequeue(queue);
	while (point != NULL)
	{
		free(point);
		point = ft_dequeue(queue);
	}
}

bool	bfs(t_map map)
{
	t_point	*point;
	t_bfs	data;

	if (!bfs_init(&data, map))
		return (false);
	while (data.queue.front)
	{
		point = (t_point *)ft_dequeue(&data.queue);
		if (!point)
			return (bfs_free(&data.queue, data.visited, map.height), false);
		if (ft_strchr("0NSEW", map.raw[point->y][point->x])
			|| !visit_neighbourgs(*point, &data))
			return (free(point), bfs_free(&data.queue, data.visited,
					map.height), false);
		free(point);
	}
	if (has_invalid_spaces(map, data.visited))
		return (bfs_free(&data.queue, data.visited, map.height), false);
	bfs_free(&data.queue, data.visited, map.height);
	return (true);
}
