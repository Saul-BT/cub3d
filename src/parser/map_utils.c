/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:37:26 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/14 21:38:44 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	set_texture(char ***texture, char **texture_ids, char **line)
{
	int	tex_id;
	int	tex_id_len;

	tex_id = 0;
	while (tex_id < 6)
	{
		tex_id_len = ft_strlen(texture_ids[tex_id]);
		if (ft_strncmp(texture_ids[tex_id], *line, tex_id_len) == 0)
		{
			if ((*texture)[tex_id])
			{
				tex_id++;
				continue ;
			}
			(*texture)[tex_id] = ft_strtrim(*line + tex_id_len, " \n");
			if (!(*texture)[tex_id])
				return (free(*line), false);
			break ;
		}
		tex_id++;
	}
	if (tex_id == 6)
		return (free(*line), false);
	free(*line);
	return (true);
}

void	ids_init(char **texture_ids)
{
	texture_ids[NORTH] = "NO ";
	texture_ids[SOUTH] = "SO ";
	texture_ids[EAST] = "EA ";
	texture_ids[WEST] = "WE ";
	texture_ids[C_FLOOR] = "F ";
	texture_ids[C_CEILING] = "C ";
}

int	get_max_map_width(t_map *map)
{
	int	y;
	int	max_x;
	int	cur_len;

	y = 0;
	max_x = 0;
	while (map->raw[y])
	{
		cur_len = ft_strlen(map->raw[y]);
		if (cur_len > max_x)
			max_x = cur_len;
		y++;
	}
	return (max_x);
}
