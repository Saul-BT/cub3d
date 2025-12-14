/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:41:42 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 12:28:56 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_cube(t_win *win, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < TILE)
	{
		i = 0;
		while (i < TILE)
		{
			safe_put_pixel(win->mmap, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

static t_point	setup_bresenham(t_point *p, t_point *dir, t_point *from,
		t_point *to)
{
	t_point	diff;

	p->x = from->x;
	p->y = from->y;
	dir->x = -1;
	dir->y = -1;
	if (from->x < to->x)
		dir->x = 1;
	if (from->y < to->y)
		dir->y = 1;
	diff.x = abs(to->x - from->x);
	diff.y = abs(to->y - from->y);
	return (diff);
}

void	draw_line(t_win *win, t_point from, t_point to, uint32_t color)
{
	t_point	point;
	t_point	diff;
	t_point	dir;
	int		err;
	int		factor;

	diff = setup_bresenham(&point, &dir, &from, &to);
	err = diff.x - diff.y;
	while (!(point.x == to.x && point.y == to.y))
	{
		safe_put_pixel(win->mmap, point.x, point.y, color);
		factor = err * 2;
		if (factor > -diff.y)
		{
			point.x += dir.x;
			err -= diff.y;
		}
		if (factor < diff.x)
		{
			point.y += dir.y;
			err += diff.x;
		}
	}
}

void	draw_circle(t_win *win, int center_x, int center_y)
{
	int	radius;
	int	x;
	int	y;
	int	dx;
	int	dy;

	radius = TILE / 4;
	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			dx = x - center_x;
			dy = y - center_y;
			if (dx * dx + dy * dy <= radius * radius)
				safe_put_pixel(win->mmap, x, y, RED);
			x++;
		}
		y++;
	}
}
