/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:13:26 by gade-oli          #+#    #+#             */
/*   Updated: 2025/10/22 21:35:43 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIN_NAME "cub3d"
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720

# define SUCCESS 0
# define ERROR 1

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
}	t_mlx;

typedef struct	s_cub3d
{
	t_mlx *mlx;
}	t_cub3d;

#endif
