/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:42:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 22:24:03 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_ray(t_cub *cub, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->map_x = (int)cub->player.pos.x;
	ray->map_y = (int)cub->player.pos.y;
	ray->ray_dir_x = cub->player.dir.x + cub->player.plane.x * ray->camera_x;
	if (ray->ray_dir_x == 0)
		ray->ray_dir_x = DBL_EPSILON;
	ray->ray_dir_y = cub->player.dir.y + cub->player.plane.y * ray->camera_x;
	if (ray->ray_dir_y == 0)
		ray->ray_dir_y = DBL_EPSILON;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	init_step(t_cub *cub, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub->player.pos.x - ray->map_x);
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub->player.pos.x);
	}
	ray->side_dist_x *= ray->delta_dist_x;
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub->player.pos.y - ray->map_y);
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub->player.pos.y);
	}
	ray->side_dist_y *= ray->delta_dist_y;
}

static void	perform_dda(t_cub *cub, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= cub->map.width || ray->map_y < 0
			|| ray->map_y >= cub->map.height)
			break ;
		if (cub->map.raw[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calculate_wall_height(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - cub->player.pos.x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - cub->player.pos.y + (1
					- ray->step_y) / 2) / ray->ray_dir_y;
	if (ray->perp_wall_dist < DBL_EPSILON)
		ray->perp_wall_dist = DBL_EPSILON;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	raycast(t_cub *cub)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(cub, &ray, x);
		init_step(cub, &ray);
		perform_dda(cub, &ray);
		calculate_wall_height(cub, &ray);
		render_ceiling(cub, &ray, x);
		render_wall(cub, &ray, x);
		render_floor(cub, &ray, x);
		x++;
	}
}
