/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:30:48 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 11:29:47 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static uint32_t	get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
    int index;

	if (x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
		return (BLACK);
    index = (y * tex->width + x) * 4;
	return ((tex->pixels[index] << 24) |
            (tex->pixels[index + 1] << 16) |
            (tex->pixels[index + 2] << 8) |
            (tex->pixels[index + 3]));
}

static mlx_texture_t	*get_current_texture(t_cub *cub, t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->ray_dir_x > 0)
            return (cub->win->wall_east);
        else
            return (cub->win->wall_west);
    }
    else
    {
        if (ray->ray_dir_y > 0)
            return (cub->win->wall_south);
        else
            return (cub->win->wall_north);
    }
}

//TODO: bonus include texture loading for ceiling and floor
void	render_ceiling(t_cub *cub, t_ray *ray, int x)
{
	int y;

	y = 0;
	while (y < ray->draw_start)
	{
		safe_put_pixel(cub->win->game, x, y, cub->win->ceiling_color);
		y++;
	}
}

//TODO: bonus include texture loading for ceiling and floor
void	render_floor(t_cub *cub, t_ray *ray, int x)
{
	int y;

	y = ray->draw_end;
	while (y < WIN_HEIGHT)
	{
		safe_put_pixel(cub->win->game, x, y, cub->win->floor_color);
		y++;
	}
}

void	render_wall(t_cub *cub, t_ray *ray, int x)
{
	mlx_texture_t	*tex;
	uint32_t		color;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				y;

	tex = get_current_texture(cub, ray);
	if (ray->side == 0)
		wall_x = cub->player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = cub->player->x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos % tex->height;
		color = get_texture_pixel(tex, tex_x, tex_y);
		safe_put_pixel(cub->win->game, x, y, color);
		tex_pos += step;
		y++;
	}
}