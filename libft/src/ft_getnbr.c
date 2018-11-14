/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrill <cbrill@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:57:41 by cbrill            #+#    #+#             */
/*   Updated: 2018/09/13 13:56:00 by cbrill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int	ft_getnbr(char *str, int *error)
{
	int	nb;
	int	neg;

	nb = 0;
	neg = 1;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '-')
			return (*error = 1);
		else if (*str == '-')
		{
			neg = -1;
			str++;
			continue ;
		}
		nb = nb * 10 + (*str - 48);
		if (nb > INT_MAX || nb < 0)
			return (*error = 1);
		str++;
	}
	*error = 0;
	return (nb * neg);
}
