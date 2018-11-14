/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damiandavis <damiandavis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:08:58 by pbondoer          #+#    #+#             */
/*   Updated: 2018/11/13 11:06:16 by damiandavis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		init_player(t_player *p, t_map *m)
{
	int	x;
	int	y;
	int	t;

	y = -1;
	t = 0;
	while (++y < m->height)
	{
		x = -1;
		while (++x < m->width)
		{
			if (!(t = get_tile(m, x, y)))
				break ;
		}
		if (!t)
			break ;
	}
	p->x = x + 0.5f;
	p->y = y + 0.5f;
	p->d = (t_vector){1.0f, 0.0f};
	p->p = (t_vector){0.0f, 2.0f / 3.0f};
}

static void	rotate(t_vector *v, float angle)
{
	float x;
	float c;
	float s;

	x = v->x;
	c = cos(angle);
	s = sin(angle);
	v->x = v->x * c - v->y * s;
	v->y = x * s + v->y * c;
}

void		rotate_player(t_player *p, float angle)
{
	rotate(&p->d, angle);
	rotate(&p->p, angle);
}

void		move_player(t_player *p, t_map *m, float distance)
{
	if (!get_tile(m, p->x + distance * p->d.x, p->y))
		p->x += distance * p->d.x;
	if (!get_tile(m, p->x, p->y + distance * p->d.y))
		p->y += distance * p->d.y;
}
