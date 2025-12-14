/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:15:44 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/08 18:12:41 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	all_valid_chars(char **map)
{
	size_t	y;
	char	*trimmed;

	y = 0;
	while (map[y])
	{
		trimmed = ft_strtrim(map[y], " 01NSEW");
		if (!trimmed)
			return (false);
		if (ft_strlen(trimmed) > 0)
		{
			free(trimmed);
			return (false);
		}
		free(trimmed);
		y++;
	}
	return (true);
}

bool	is_one_player(char **map)
{
	size_t	x;
	size_t	y;
	bool	has_player;

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
					return (false);
				has_player = true;
			}
			x++;
		}
		y++;
	}
	return (has_player);
}

// FIXME: .cub.cub
bool	is_filename_valid(char *filename)
{
	char	*match;
	char	before_ext;

	match = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (!match)
		return (false);
	if (filename == match)
		return (false);
	before_ext = *(filename + (match - filename) - 1);
	return (before_ext != '/');
}
