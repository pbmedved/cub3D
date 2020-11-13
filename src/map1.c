/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:19:54 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/18 10:29:25 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			create_map(int fd, t_map *map, t_file *file)
{
	map->map = map_alloc(map->map_h + 1);
	parse_map(fd, file, map);
	check_map(map);
}

int				map_check(t_map *m, int y, int x, char c)
{
	if (m->map[y][x] == c)
		return (1);
	return (0);
}
