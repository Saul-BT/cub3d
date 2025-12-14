/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:15:44 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/14 21:25:20 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	all_valid_chars(char **map)
{
	int		y;
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
	int		x;
	int		y;
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

bool	is_filename_valid(char *filename)
{
	char	*match;
	char	before_ext;

	match = ft_strnstr(filename + 1, ".cub", ft_strlen(filename + 1));
	if (!match)
	{
		ft_error("error: mapfile name should has the '.cub' extension.");
		return (false);
	}
	before_ext = *(filename + (match - filename) - 1);
	if (before_ext == '/')
	{
		ft_error("error: mapfile name should has the '.cub' extension.");
		return (false);
	}
	return (true);
}
