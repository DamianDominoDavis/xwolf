/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damiandavis <damiandavis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 10:44:47 by pbondoer          #+#    #+#             */
/*   Updated: 2018/11/09 19:35:57 by damiandavis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_color	c(int v)
{
	t_color c;

	c.value = v;
	return (c);
}

t_color		clerp(t_color c1, t_color c2, double p)
{
	t_color c;

	if (c1.value == c2.value)
		return (c1);
	p = (p < 0.0f) ? 0.0f : (p > 1.0f ? 1.0f : p);
	c.rgba = (t_rgba){
		(char)((double)c1.rgba.r + p * (double)(c2.rgba.r - c1.rgba.r)),
		(char)((double)c1.rgba.g + p * (double)(c2.rgba.g - c1.rgba.g)),
		(char)((double)c1.rgba.b + p * (double)(c2.rgba.b - c1.rgba.b)),
		0};
	return (c);
}

static void		draw_floor(t_mlx *mlx, t_ray *r, int x, int y)
{
	float	cur;
	float	weight;
	int		fx;
	int		fy;

	while (y < WIN_HEIGHT)
	{
		cur = WIN_HEIGHT / (2.0f * y - WIN_HEIGHT);
		weight = cur / r->dist;
		fx = (int)((weight * r->fx + (1.0f - weight) * mlx->player.x) *
			mlx->floor->width) % mlx->floor->width;
		fy = (int)((weight * r->fy + (1.0f - weight) * mlx->player.y) *
			mlx->floor->height) % mlx->floor->height;
		image_set_pixel(mlx->image, x, y, clerp(c(0x0), get_pixel(mlx->floor,
			fx, fy), 1.0f - cur / VIEW_DIST).value);
		fx = (int)((weight * r->fx + (1.0f - weight) * mlx->player.x) *
			mlx->ceiling->width) % mlx->ceiling->width;
		fy = (int)((weight * r->fy + (1.0f - weight) * mlx->player.y) *
			mlx->ceiling->height) % mlx->ceiling->height;
		image_set_pixel(mlx->image, x, WIN_HEIGHT - y, clerp(c(0x0),
			get_pixel(mlx->ceiling, fx, fy), 1.0f - cur / VIEW_DIST).value);
		y++;
	}
}

static void		draw_column(t_mlx *mlx, t_ray *r, int x)
{
	int		y;
	int		start;
	int		end;
	int		tex_y;

	if (r->texture == NULL)
		return ;
	start = (WIN_HEIGHT - r->height) / 2;
	end = start + r->height;
	if (start < 0)
		start = 0;
	if (end > WIN_HEIGHT - 1)
		end = WIN_HEIGHT - 1;
	y = start;
	while (y < end)
	{
		tex_y = ((y - WIN_HEIGHT * 0.5f + r->height * 0.5f) *
			r->texture->height) / r->height;
		image_set_pixel(mlx->image, x, y++, clerp(c(0x0),
			get_pixel(r->texture, r->tex_x, tex_y), r->light).value);
	}
	draw_floor(mlx, r, x, y);
}

void			render(t_mlx *mlx)
{
	int		x;
	t_ray	ray;
	float	camera;

	clear_image(mlx->image);
	x = 0;
	while (x < WIN_WIDTH)
	{
		camera = 2.0f * x / WIN_WIDTH - 1.0f;
		ray.x = mlx->player.d.x + mlx->player.p.x * camera;
		ray.y = mlx->player.d.y + mlx->player.p.y * camera;
		cast(&ray, mlx->map, &mlx->player, mlx->tex);
		draw_column(mlx, &ray, x);
		x++;
	}
	draw_minimap(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
}
