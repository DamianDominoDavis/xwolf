/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrill <cbrill@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:29:30 by cbrill            #+#    #+#             */
/*   Updated: 2018/11/15 13:34:19 by cbrill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		die(char *reason, int r)
{
	ft_putendl(reason);
	exit(r);
	return (r);
}

static int		hook_close(t_mlx *mlx)
{
	(void)mlx;
	die(NULL, 0);
	return (0);
}

static int		hook_keydown(int key, t_mlx *mlx)
{
	if (key == K_ESC)
		die("Done.", 0);
	if (key == K_LEFT)
		rotate_player(&mlx->player, -5.0f / 180.0f * M_PI);
	if (key == K_RIGHT)
		rotate_player(&mlx->player, 5.0f / 180.0f * M_PI);
	if (key == K_UP)
		move_player(&mlx->player, mlx->map, 0.1f);
	if (key == K_DOWN)
		move_player(&mlx->player, mlx->map, -0.1f);
	render(mlx);
	return (0);
}

static t_mlx	*init(void)
{
	t_mlx	*mlx;

	if (!(mlx = ft_memalloc(sizeof(t_mlx)))
		|| !(mlx->mlx = mlx_init())
		|| !(mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT,
			"wolf3d"))
		|| !(mlx->image = new_image(mlx, WIN_WIDTH, WIN_HEIGHT)))
	{
		if (mlx)
		{
			if (mlx->mlx)
			{
				if (mlx->window)
					mlx_destroy_window(mlx->mlx, mlx->window);
				if (mlx->image)
					del_image(mlx, mlx->image);
				free(mlx->mlx);
			}
			free(mlx);
		}
		mlx = NULL;
	}
	return (mlx);
}

int				main(int argc, char **argv)
{
	t_mlx		*mlx;
	t_map		*map;

	if (argc < 2)
		return (die("usage: ./wolf3d mapfile", 0));
	else if (!(mlx = init()))
		return (die("fatal: mlx init", 1));
	else if (!load_textures(mlx))
		return (die("fatal: texure load", 1));
	else if (!(map = read_map(argv[1], mlx->max_tex)))
		return (die("fatal: bad map", 1));
	mlx->map = map;
	init_player(&mlx->player, mlx->map);
	render(mlx);
	mlx_hook(mlx->window, 2, 1L << 0, hook_keydown, mlx);
	mlx_hook(mlx->window, 17, 1L << 0, hook_close, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
