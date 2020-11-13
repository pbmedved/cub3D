/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:13:00 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/18 10:40:27 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char			**map_alloc(size_t h)
{
	char		**map;

	if (!(map = (char **)malloc(h * sizeof(char*))))
		error_exit("malloc error");
	map[h - 1] = NULL;
	return (map);
}

void			map_size_calc(char *line, t_file *file, int fd)
{
	char		*subline;

	subline = NULL;
	if (file->map.map_w < (int)ft_strlen(line))
		file->map.map_w = (int)ft_strlen(line);
	file->map.map_h++;
	while (get_next_line(&subline, fd, 0))
	{
		if (subline[0] != ' ' && subline[0] != '1')
			error_exit("invalid map");
		if (file->map.map_w < (int)ft_strlen(subline))
			file->map.map_w = (int)ft_strlen(subline);
		file->map.map_h++;
		free(subline);
	}
	free(subline);
	get_next_line(&subline, fd, 0);
	if (file->map.map_w < (int)ft_strlen(subline))
		file->map.map_w = (int)ft_strlen(subline);
	file->map.map_h++;
	free(subline);
}

void			parse_map(int fd, t_file *file, t_map *map)
{
	char		*line;
	int			d;
	int			i;

	i = 0;
	d = 0;
	line = NULL;
	while (d < map->map_h)
	{
		get_next_line(&line, fd, 0);
		i++;
		if (i >= file->map_start)
		{
			map->map[d] = ft_strdup_size(line, map->map_w + 1);
			d++;
		}
		free(line);
		line = NULL;
	}
}

void			check_map_zero(t_map *map, int i, int d)
{
	if (i == 0 || i == map->map_h - 1 || d == 0 || d == map->map_w - 1)
		error_exit("map error");
	if (!ft_strchr("210NSEW", map->map[i - 1][d - 1])\
	|| !ft_strchr("210NSEW", map->map[i][d - 1])\
	|| !ft_strchr("210NSEW", map->map[i + 1][d - 1])\
	|| !ft_strchr("210NSEW", map->map[i - 1][d])\
	|| !ft_strchr("210NSEW", map->map[i + 1][d])\
	|| !ft_strchr("210NSEW", map->map[i - 1][d + 1])\
	|| !ft_strchr("210NSEW", map->map[i][d + 1])\
	|| !ft_strchr("210NSEW", map->map[i + 1][d + 1]))
		error_exit("map error");
}

void			check_map(t_map *map)
{
	int			i;
	int			d;
	int			p;

	i = 0;
	d = 0;
	p = 0;
	while (map->map[i])
	{
		while (map->map[i][d])
		{
			if (!ft_strchr("120NSEW ", map->map[i][d]))
				error_exit("map error (invalid symbols)");
			if (ft_strchr("20NSEW", map->map[i][d]))
				check_map_zero(map, i, d);
			if (ft_strchr("NSEW", map->map[i][d]))
				p++;
			d++;
		}
		d = 0;
		i++;
	}
	if (p != 1)
		error_exit("player error");
}
