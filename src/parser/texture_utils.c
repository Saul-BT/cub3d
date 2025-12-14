/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:38:06 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/14 21:23:59 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	count_color_values(char **values)
{
	int	len;

	len = 0;
	while (values[len])
		len++;
	return (len);
}

static void	color_values_free(char **values)
{
	int	len;

	len = 0;
	while (values[len])
		free(values[len++]);
	free(values);
}

static int	get_color_value(char *str_value)
{
	long	value;
	char	*trimmed;

	trimmed = ft_strtrim(str_value, " ");
	value = ft_atoi(trimmed);
	free(trimmed);
	if (value > 255 || value < 0)
		return (-1);
	return ((int)value);
}

bool	set_valid_color(char *color, uint32_t *value)
{
	int		red;
	int		green;
	int		blue;
	char	**values;

	*value = 0xFF;
	values = ft_split(color, ',');
	if (!values)
		return (false);
	if (count_color_values(values) != 3)
		return (color_values_free(values), false);
	red = get_color_value(color);
	if (red == -1)
		return (color_values_free(values), false);
	green = get_color_value(color);
	if (green == -1)
		return (color_values_free(values), false);
	blue = get_color_value(color);
	if (blue == -1)
		return (color_values_free(values), false);
	*value |= (red << 24 | green << 16 | blue << 8);
	color_values_free(values);
	return (true);
}
