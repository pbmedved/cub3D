/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screensh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:38:34 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/13 16:15:05 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#define HEADER_SIZE 122

void	fill_bmp(char **data, t_vars *vars)
{
	int i;
	int j;
	int x;
	int y;

	i = HEADER_SIZE;
	y = vars->file.h;
	while (y--)
	{
		x = -1;
		while (++x < vars->file.w)
		{
			j = (x * (vars->img->bits_per_pixel / 8))
				+ (y * vars->img->line_length);
			*(*data + i++) = *(vars->img->addr + j++);
			*(*data + i++) = *(vars->img->addr + j++);
			*(*data + i++) = *(vars->img->addr + j);
		}
	}
}

/*
** Initialize the header of bmp (char *data)
**
** HEADER
** Position | Hex	| Description
** 00		| 00	| TYPE OF BMP FILE
** 02		| 02	| TOTAL SIZE OF FILE
** 06-08	| 06-08	| RESERVED TO SIGN
** 10		| 0A	| HEADER SIZE
** =============================================================================
** HEADER INFOS
** Position | Hex	| Description
** 14		| 0E	| HEADER INFOS SIZE
** 18		| 12	| WIDTH OF IMG (PX)
** 22		| 16	| HEIGHT OF IMG (PX)
** 26		| 1A	| NUMBER OF PLANS
** 28		| 1C	| BITS PER PIXELS (1 - 4 - 8 - 24)
** 30		| 1E	| COMPRESSION TYPE
** 34		| 22	| SIZE OF IMG
** 38		| 26	| RES X PX PER METER
** 42		| 2A	| RES Y PX PER METER
** 46		| 2E	| NB OF USED COLOR (0 = MAX)
** 50		| 32	| NB OF INDEX OF COLOR (0 = ALL)
*/

void	header_bmp(char **data, t_vars *vars)
{
	unsigned int size;

	size = vars->file.h * vars->file.w * 3;
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + HEADER_SIZE);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = HEADER_SIZE;
	*(unsigned int *)(*data + 14) = HEADER_SIZE - 14;
	*(unsigned int *)(*data + 18) = vars->file.w;
	*(unsigned int *)(*data + 22) = vars->file.h;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

void	export_bmp(t_vars *vars)
{
	int				fd;
	unsigned int	size;
	unsigned int	i;
	char			*data;

	size = vars->file.h * vars->file.w * 3;
	if (!(data = malloc((size + HEADER_SIZE))))
		error_exit("malloc error");
	i = 0;
	while (i < size + HEADER_SIZE)
		data[i++] = 0;
	header_bmp(&data, vars);
	fill_bmp(&data, vars);
	if ((fd = open("screenshot.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		error_exit("open error");
	write(fd, data, (size + HEADER_SIZE));
	close(fd);
	exit(0);
}
