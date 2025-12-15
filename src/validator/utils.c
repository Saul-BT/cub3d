/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:15:44 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/15 18:05:08 by sblanco-         ###   ########.fr       */
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
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
	{
		ft_error("error: invalid map filename");
		return (false);
	}
	if (ft_strncmp(filename + (len - 4), ".cub", 4))
	{
		ft_error("error: invalid map filename");
		return (false);
	}
	if (*(filename + (len - 5)) == '/')
	{
		ft_error("error: invalid map filename");
		return (false);
	}
	return (true);
}
