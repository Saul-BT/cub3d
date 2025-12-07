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
		"101000000001",
		"100101000001",
		"10E001000001",
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
	//TODO: malloc check for map when parser is integrated
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
	{
		//free_array(cub->map); //TODO: enable when parser is integrated
		free(cub->win);
		return (ft_error("malloc error in player struct\n"));
	}
	return (SUCCESS);
}

void	free_structs(t_cub *cub)
{
	free_window(cub->win);
	free(cub->win);
	//free_array(cub->map); //TODO: enable when parser is integrated
	free(cub->player);
}