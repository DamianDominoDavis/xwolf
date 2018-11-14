/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damiandavis <damiandavis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 14:43:24 by pbondoer          #+#    #+#             */
/*   Updated: 2018/11/13 12:57:40 by damiandavis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
