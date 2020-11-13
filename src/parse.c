/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:29:18 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/18 10:48:17 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		ft_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

void			parse_resolution(char *line, t_file *file)
{
	if (file->w && file->h)
		error_exit("resolution error");
	line++;
	while (*line == ' ')
		line++;
	if (*line && ft_isdigit(*line))
		file->w = ft_simple_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	while (*line == ' ')
		line++;
	if (*line && ft_isdigit(*line))
		file->h = ft_simple_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line || !file->w || !file->h)
		error_exit("resolution error");
}

void			parse_color(char *line, t_color *color)
{
	while (*line && *line == ' ')
		line++;
	if (ft_isdigit(*line))
		color->r = ft_simple_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	while (*line && *line == ' ')
		line++;
	if (ft_isdigit(*line))
		color->g = ft_simple_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	while (*line && *line == ' ')
		line++;
	if (ft_isdigit(*line))
		color->b = ft_simple_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line != 0)
		error_exit("color parse error");
	check_color(*color);
}

void			parse_redirect_t(char *s, t_file *file, t_vars *vars)
{
	if (*s == 'N')
		parse_texture(s, &file->no, vars);
	else if (*s == 'W')
		parse_texture(s, &file->we, vars);
	else if (*s == 'E')
		parse_texture(s, &file->ea, vars);
	else if (s[0] == 'S' && s[1] == 'O')
		parse_texture(s, &file->so, vars);
	else if (*s == 'S')
		parse_texture(s, &file->s, vars);
}

void			parse_redirect_c(char *s, t_file *file)
{
	if (*s == 'F')
		parse_color(++s, &file->f);
	else if (*s == 'C')
		parse_color(++s, &file->c);
}
