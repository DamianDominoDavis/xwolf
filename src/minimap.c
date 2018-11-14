/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damiandavis <damiandavis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 16:13:55 by pbondoer          #+#    #+#             */
/*   Updated: 2018/11/09 19:35:33 by damiandavis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		draw_square(t_image *i, t_color c, t_vector v, int size)
{
	int	x;
	int	y;

	y = size * (v.y + 2) - 1;
	while (++y < size * (v.y + 3))
	{
		x = size * (v.x + 2) - 1;
		while (++x < size * (v.x + 3))
			image_set_pixel(i, x, y, clerp(get_pixel(i, x, y), c, 0.5f).value);
	}
}

void			draw_minimap(t_mlx *mlx)
{
	t_vector	v;
	int			size;

	size = WIN_WIDTH / 10 / mlx->map->width;
	v.x = -1;
	while (++v.x < mlx->map->width)
	{
		v.y = -1;
		while (++v.y < mlx->map->height)
			if (get_tile(mlx->map, v.x, v.y))
				draw_square(mlx->image, (t_color)0xFFFFFF, v, size);
	}
	v = (t_vector){mlx->player.x - 0.5f, mlx->player.y - 0.5f};
	draw_square(mlx->image, (t_color)0x00, v, size);
	v.x += mlx->player.d.x;
	v.y += mlx->player.d.y;
	draw_square(mlx->image, (t_color)0xFF0000, v, size);
}
