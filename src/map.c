/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrill <cbrill@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:04:17 by cbrill            #+#    #+#             */
/*   Updated: 2018/11/15 16:04:07 by cbrill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_map			*cancel(t_map **map)
{
	int	i;

	i = -1;
	if (map && *map)
	{
		if ((*map)->values)
		{
			while (++i < (*map)->height)
				if ((*map)->values[i])
					free((*map)->values[i]);
			free((*map)->values);
		}
		free(*map);
	}	
	return (*map = NULL);
}

static int		size(t_map *map, char *path)
{
	char	*line;
	int		fd;

	line = NULL;
	if (0 > (fd = open(path, O_RDONLY)) || 1 != get_next_line(fd, &line))
		return (0);
	map->width = ft_wordcount(line, ' ');
	free(line);
	map->height = 1;
	while (1 == get_next_line(fd, &line))
	{
		if (map->width != (int)ft_wordcount(line, ' '))
		{
			free(line);
			return (0);
		}
		free(line);
		map->height++;
	}
	return (map->height);
}

static void		fill(t_map *map, int fd, int max)
{
	int		i;
	int		j;
	char	*line;
	char	**words;

	i = -1;
	while (++i < map->height)
	{
		get_next_line(fd, &line);
		words = ft_strsplit(line, ' ');
		free(line);
		map->values[i] = (int*)malloc(sizeof(int) * map->width);
		j = -1;
		while (++j < map->width)
		{
			map->values[i][j] = ft_atoi(words[j]);
			if (map->values[i][j] < 0 || map->values[i][j] > max)
				map->values[i][j] = -1;
			free(words[j]);
		}
		free(words);
	}
}

static t_map	*accept(t_map *m, int max)
{
	int	x;
	int	y;
	int	hole;
	int	bord;

	hole = 0;
	bord = 1;
	y = -1;
	while (++y < m->height)
	{
		x = -1;
		while (++x < m->width)
		{
			if (get_tile(m, x, y) < 0 || get_tile(m, x, y) > max)
				return (cancel(&m));
			if (!hole)
				hole = (get_tile(m, x, y) == 0);
			if (bord && (x == 0 || x == m->width - 1 || y == 0
				|| y == m->width - 1))
				bord = (get_tile(m, x, y) != 0);
		}
	}
	if (!hole || !bord)
		return (cancel(&m));
	return (m);
}

t_map			*read_map(char *path, int max)
{
	t_map	*map;

	if (!(map = malloc(sizeof(t_map)))
		|| !size(map, path)
		|| !(map->values = (int**)malloc(sizeof(int*) * map->height)))
	{
		if (map)
			free(map);
		return (NULL);
	}
	fill(map, open(path, O_RDONLY), max);
	return (accept(map, max));
}
