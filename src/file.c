/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:18:30 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/18 10:01:05 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			set_file(t_file *file)
{
	file->f = (t_color){300, 300, 300};
	file->c = (t_color){300, 300, 300};
	file->map.map_h = 0;
	file->map.map_w = 0;
	file->w = 0;
	file->h = 0;
	file->map.map = NULL;
}

void			resolution_check(t_file *file, t_vars *vars)
{
	int x;
	int y;

	mlx_get_screen_size(vars->mlx, &x, &y);
	if (file->w > x)
		file->w = x;
	if (file->h > y)
		file->h = y;
}

void			create_config_file(char *s, t_file *file, t_vars *vars)
{
	int fd;

	fd = open(s, O_RDONLY);
	parse_file(fd, file, vars);
	close(fd);
	fd = open(s, O_RDONLY);
	create_map(fd, &file->map, file);
	close(fd);
	check_textures(file);
}
