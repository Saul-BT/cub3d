/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:41:12 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/08 18:57:15 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	all_textures_setted(char **texture)
{
	return (texture[NORTH] && texture[SOUTH] && texture[WEST] && texture[EAST]
		&& texture[C_FLOOR] && texture[C_CEILING]);
}

bool	set_texture(char ***texture, int fd)
{
	int			tex_id;
	int			tex_id_len;
	char		*line;
	static char	*texture_ids[6];

	texture_ids[NORTH] = "NO ";
	texture_ids[SOUTH] = "SO ";
	texture_ids[EAST] = "EA ";
	texture_ids[WEST] = "WE ";
	texture_ids[C_FLOOR] = "F ";
	texture_ids[C_CEILING] = "C ";
	*texture = ft_calloc(6, sizeof(char *));
	if (!*texture)
		return (false);
	while (!all_textures_setted(*texture) && (line = get_next_line(fd)) != NULL)
	{
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		tex_id = 0;
		while (tex_id < 6)
		{
			tex_id_len = ft_strlen(texture_ids[tex_id]);
			if (ft_strncmp(texture_ids[tex_id], line, tex_id_len) == 0)
			{
				if ((*texture)[tex_id])
				{
					tex_id++;
					continue ;
				}
				(*texture)[tex_id] = ft_strtrim(line + tex_id_len, " \n");
				if (!(*texture)[tex_id])
					return (free(line), false);
				break ;
			}
			tex_id++;
		}
		if (tex_id == 6)
			return (free(line), false);
		free(line);
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
	while ((line = get_next_line(fd)) != NULL)
	{
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
	size_t	y;
	size_t	cur_len;
	size_t	max_x;
	char	*reshaped;

	y = 0;
	max_x = 0;
	while (map->raw[y])
	{
		cur_len = ft_strlen(map->raw[y]);
		if (cur_len > max_x)
			max_x = cur_len;
		y++;
	}
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
	char *line;
	char *raw_map;

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