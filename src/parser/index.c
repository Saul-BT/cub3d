/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:41:12 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/14 21:38:22 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	all_textures_setted(char **texture)
{
	return (texture[NORTH] && texture[SOUTH] && texture[WEST] && texture[EAST]
		&& texture[C_FLOOR] && texture[C_CEILING]);
}

bool	set_textures(char ***texture, int fd)
{
	char		*line;
	static char	*texture_ids[6];

	ids_init(texture_ids);
	*texture = ft_calloc(6, sizeof(char *));
	if (!*texture)
		return (false);
	while (!all_textures_setted(*texture))
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		if (!set_texture(texture, texture_ids, &line))
			return (false);
	}
	return (true);
}

static char	*read_map(char *head, int fd)
{
	char	*line;
	char	*tmp;
	char	*map;

	map = head;
	tmp = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line == '\n')
		{
			free(map);
			free(line);
			return (false);
		}
		tmp = ft_strjoin(map, line);
		free(map);
		free(line);
		if (!tmp)
			return (NULL);
		map = tmp;
	}
	return (map);
}

/**
 * ex:
 * {                        {
 *   "1111111",               "1111111",
 *   "1001",        ===>      "1001   ",
 *   "10001",       ===>      "10001  ",
 *   " 111",                  " 111   ",
 * }                        }
 */
static bool	reshape_map(t_map *map)
{
	int		y;
	int		max_x;
	int		cur_len;
	char	*reshaped;

	max_x = get_max_map_width(map);
	if (max_x == 0)
		return (false);
	y = 0;
	while (map->raw[y])
	{
		reshaped = ft_calloc(max_x + 1, sizeof(char));
		if (!reshaped)
			return (false);
		ft_memset(reshaped, ' ', max_x);
		ft_memcpy(reshaped, map->raw[y], ft_strlen(map->raw[y]));
		free(map->raw[y]);
		map->raw[y] = reshaped;
		y++;
	}
	map->height = y;
	map->width = max_x;
	return (true);
}

bool	set_map(t_map *map, int fd)
{
	char	*line;
	char	*raw_map;

	line = get_next_line(fd);
	if (!line)
		return (false);
	if (*line != '\n')
		return (free(line), false);
	while (line != NULL && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (false);
	raw_map = read_map(line, fd);
	if (!raw_map)
		return (false);
	map->raw = ft_split(raw_map, '\n');
	free(raw_map);
	if (!map->raw)
		return (false);
	if (!reshape_map(map))
		return (false);
	return (true);
}
