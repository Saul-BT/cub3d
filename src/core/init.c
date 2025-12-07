/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:10:08 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/05 20:10:09 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//TODO: delete when parser integrated
static char** get_mock_map(void)
{
	static char *map_data[] = {
		"111111111111",
		"100100000001",
		"101001000000",
		"11E001000000",
		"111111111111",
		NULL
	};
	return (map_data);
}

int	init_structs(t_cub *cub)
{
	cub->win = malloc(sizeof(t_win));
	if (!cub->win)
		return (ft_error("malloc error in window struct\n"));
	if (init_window(cub->win) == ERROR)
		return (ERROR);
	cub->map = get_mock_map();
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
	{
		//free_array(cub->map);
		free(cub);
		return (ft_error("malloc error in player struct\n"));
	}
	return (SUCCESS);
}