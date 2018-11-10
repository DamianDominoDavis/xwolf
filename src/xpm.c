/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damiandavis <damiandavis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 04:12:45 by pbondoer          #+#    #+#             */
/*   Updated: 2018/11/09 19:36:11 by damiandavis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_image	*xpm_image(char *xpm, t_mlx *mlx)
{
	t_image		*img;

	if ((img = ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	if ((img->image = mlx_xpm_file_to_image(mlx->mlx, xpm, &img->width,
			&img->height)) == NULL)
		return (del_image(mlx, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
		&img->endian);
	img->bpp /= 8;
	img->width = img->stride / img->bpp;
	img->height = img->stride / img->bpp;
	return (img);
}
