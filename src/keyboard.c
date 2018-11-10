/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damiandavis <damiandavis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 05:33:43 by pbondoer          #+#    #+#             */
/*   Updated: 2018/11/09 19:35:20 by damiandavis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		hook_keydown(int key, t_mlx *mlx)
{
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
	if (key == K_LEFT)
		rotate_player(&mlx->player, -2.0f / 180.0f * M_PI);
	if (key == K_RIGHT)
		rotate_player(&mlx->player, 2.0f / 180.0f * M_PI);
	if (key == K_UP)
		move_player(&mlx->player, mlx->map, 0.05f);
	if (key == K_DOWN)
		move_player(&mlx->player, mlx->map, -0.05f);
	render(mlx);
	return (0);
}
