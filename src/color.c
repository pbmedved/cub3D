/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 10:56:14 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/13 16:31:53 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void			check_color(t_color a)
{
	if (a.r > 255 || a.r < 0)
		error_exit("color error");
	if (a.g > 255 || a.g < 0)
		error_exit("color error");
	if (a.b > 255 || a.b < 0)
		error_exit("color error");
}
