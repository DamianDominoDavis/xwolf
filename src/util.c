/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrill <cbrill@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:58:16 by cbrill            #+#    #+#             */
/*   Updated: 2018/11/15 13:34:45 by cbrill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				get_tile(t_map *m, int x, int y)
{
	if (x < 0 || y < 0 || x > m->width - 1 || y > m->height - 1)
		return (0);
	return (m->values[y][x]);
}

t_image			*xpm_image(char *xpm, t_mlx *mlx)
{
	t_image		*img;

	if (!(img = malloc(sizeof(t_image)))
		|| !(img->image = mlx_xpm_file_to_image(mlx->mlx, xpm, &img->width,
			&img->height)))
		return (del_image(mlx, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
		&img->endian);
	img->bpp /= 8;
	img->width = img->stride / img->bpp;
	img->height = img->stride / img->bpp;
	return (img);
}

int				load_textures(t_mlx *mlx)
{
	static char	*map[TEX_MAP_SIZE] = { "textures/brick.xpm",
		"textures/wood.xpm", "textures/metal.xpm", "textures/stone.xpm",
		"textures/grass.xpm", NULL };
	static char	*himap[TEX_MAP_SIZE] = { "textures_hi/brick.xpm",
		"textures_hi/wood.xpm", "textures_hi/metal.xpm",
		"textures_hi/stone.xpm", "textures_hi/grass.xpm", NULL };
	int			i;

	i = 1;
	while (i < TEX_MAP_SIZE && map[i - 1])
		if (!(mlx->tex[i] = xpm_image((HI_RES ? himap[i - 1]
			: map[i - 1]), mlx)))
		{
			i = 0;
			while (i < TEX_MAP_SIZE)
				del_image(mlx, mlx->tex[i++]);
			return (0);
		}
		else
			i++;
	mlx->max_tex = i - 1;
	mlx->tex[0] = NULL;
	mlx->floor = mlx->tex[2];
	mlx->ceiling = mlx->tex[4];
	return (1);
}

static void		draw_square(t_image *i, t_color c, t_vector v, int size)
{
	int	x;
	int	y;

	y = size * (v.y + 2) - 1;
	while (++y < size * (v.y + 3))
	{
		x = size * (v.x + 2) - 1;
		while (++x < size * (v.x + 3))
			image_set_pixel(i, x, y, nonce(get_pixel(i, x, y), c, 0.5f).value);
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
