/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrill <cbrill@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:29:34 by cbrill            #+#    #+#             */
/*   Updated: 2018/11/15 13:34:13 by cbrill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	image_set_pixel(t_image *image, int x, int y, int color)
{
	if (!(x < 0 || y < 0 || x >= image->width || y >= image->height))
		*(int *)(image->ptr + ((x + y * image->width) * image->bpp)) = color;
}

void	clear_image(t_image *image)
{
	ft_bzero(image->ptr, image->width * image->height * image->bpp);
}

t_color	get_pixel(t_image *image, int x, int y)
{
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ((t_color)0);
	return ((t_color)*(int *)(image->ptr + ((x + y * image->width) *
		image->bpp)));
}

t_image	*del_image(t_mlx *mlx, t_image *img)
{
	if (img)
	{
		if (img->image)
			mlx_destroy_image(mlx->mlx, img->image);
		free(img);
	}
	return (NULL);
}

t_image	*new_image(t_mlx *mlx, int w, int h)
{
	t_image		*img;

	if (!(img = ft_memalloc(sizeof(t_image)))
		|| !(img->image = mlx_new_image(mlx->mlx, w, h)))
		return (del_image(mlx, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
		&img->endian);
	img->bpp /= 8;
	img->width = w;
	img->height = h;
	return (img);
}
