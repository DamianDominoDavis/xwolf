/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrill <cbrill@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:29:33 by cbrill            #+#    #+#             */
/*   Updated: 2018/11/15 15:09:20 by cbrill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include "libft.h"
# include "mlx.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define VIEW_DIST 10
# define TEX_MAP_SIZE 6
# define HI_RES 1

# ifdef __linux__
#  define K_ESC			65307
#  define K_UP			65362
#  define K_DOWN		65364
#  define K_LEFT		65361
#  define K_RIGHT		65363
# else
#  define K_ESC			53
#  define K_UP			126
#  define K_DOWN		125
#  define K_LEFT		123
#  define K_RIGHT		124
# endif

typedef struct	s_rgba
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				t_rgba;

typedef union	u_color
{
	int		value;
	t_rgba	rgba;
}				t_color;

typedef struct	s_image
{
	void	*image;
	char	*ptr;
	int		bpp;
	int		stride;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct	s_map
{
	int	width;
	int	height;
	int	**values;
}				t_map;

typedef struct	s_vector
{
	float	x;
	float	y;
}				t_vector;

typedef struct	s_cast
{
	int		mx;
	int		my;
	float	sx;
	float	sy;
	float	dx;
	float	dy;
	int		stepx;
	int		stepy;
	float	wall;
}				t_cast;

typedef struct	s_ray
{
	float	x;
	float	y;
	int		side;
	float	dist;
	float	light;
	int		height;
	t_image	*texture;
	int		tex_x;
	float	fx;
	float	fy;
}				t_ray;

typedef struct	s_player
{
	float		x;
	float		y;
	t_vector	d;
	t_vector	p;
}				t_player;

typedef struct	s_mlx
{
	void		*mlx;
	void		*window;
	t_image		*image;
	t_map		*map;
	t_player	player;
	t_image		*tex[TEX_MAP_SIZE];
	int			max_tex;
	t_image		*floor;
	t_image		*ceiling;
}				t_mlx;

t_image			*new_image(t_mlx *mlx, int w, int h);
t_image			*xpm_image(char *xpm, t_mlx *mlx);
t_color			get_pixel(t_image *image, int x, int y);
void			image_set_pixel(t_image *image, int x, int y, int color);
t_image			*del_image(t_mlx *mlx, t_image *img);

void			init_player(t_player *p, t_map *m);
void			rotate_player(t_player *p, float angle);
void			move_player(t_player *p, t_map *m, float distance);

void			cast(t_ray *r, t_map *m, t_player *p, t_image *tex[]);

t_map			*cancel(t_map **map);
t_map			*read_map(char *path, int max);

t_color			nonce(t_color c1, t_color c2, double p);
void			render(t_mlx *mlx);

int				get_tile(t_map *m, int x, int y);
int				load_textures(t_mlx *mlx);
void			draw_minimap(t_mlx *mlx);

#endif
