/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:44:51 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/18 09:08:25 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		choose_png_or_xpm(char *s, t_texture *texture, t_vars *vars)
{
	if (s[ft_strlen(s) - 1] == 'g')
	{
		if (!(texture->img = mlx_png_file_to_image(vars->mlx, s, \
		&texture->w, &texture->h)))
			error_exit("texture parse error");
	}
	else
	{
		if (!(texture->img = mlx_xpm_file_to_image(vars->mlx, s, \
		&texture->w, &texture->h)))
			error_exit("texture parse error");
	}
}

void			parse_texture(char *s, t_texture *texture, t_vars *vars)
{
	if (texture->img)
		error_exit("texture parse error");
	while (*s != ' ')
		s++;
	while (*s == ' ')
		s++;
	choose_png_or_xpm(s, texture, vars);
	if (!(texture->img->addr = mlx_get_data_addr(texture->img, \
	&texture->img->bits_per_pixel, &texture->img->line_length, \
	&texture->img->endian)))
		error_exit("texture get addr error");
	texture->ch = 0;
	texture->cw = 0;
}

void			check_textures(t_file *file)
{
	if (!file->no.img || !file->so.img || !file->s.img\
	|| !file->we.img || !file->ea.img)
		error_exit("texture parse error");
}
