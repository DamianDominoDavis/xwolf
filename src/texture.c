/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damiandavis <damiandavis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 04:19:00 by pbondoer          #+#    #+#             */
/*   Updated: 2018/11/09 21:05:30 by damiandavis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			load_textures(t_mlx *mlx)
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
		if (!(mlx->tex[i] = xpm_image((HI_RES ? himap[i - 1] : map[i - 1]), mlx)))
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
