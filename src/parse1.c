/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 10:45:36 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/18 10:49:54 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				is_file_filled(t_file *file)
{
	if (!file->no.img || !file->so.img || !file->s.img\
	|| !file->we.img || !file->ea.img)
		return (0);
	if (!file->w || !file->h)
		return (0);
	if (file->c.r > 255 || file->c.g > 255 || file->c.b > 255)
		return (0);
	if (file->f.r > 255 || file->f.g > 255 || file->f.b > 255)
		return (0);
	return (1);
}

void			parse_file(int fd, t_file *file, t_vars *vars)
{
	char		*line;
	char		*res;

	file->map_start = 0;
	line = NULL;
	while (get_next_line(&line, fd, 0))
	{
		file->map_start++;
		res = line;
		while (*res == ' ' && !is_file_filled(file))
			res++;
		if (*res && !ft_strchr("NSWERFC1 ", *res))
			error_exit("file error");
		if (*res == 'R')
			parse_resolution(res, file);
		else if (ft_strchr("NSWE", *res))
			parse_redirect_t(res, file, vars);
		else if (ft_strchr("CF", *res))
			parse_redirect_c(res, file);
		else if (is_file_filled(file) && (ft_strchr(" 10", *res)))
			map_size_calc(res, file, fd);
		free(line);
	}
	free(line);
}
