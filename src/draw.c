/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:15:32 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/19 11:54:25 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	if (color >= 0)
	{
		dst = data->addr + (y * data->line_length\
		+ x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void			draw_wall(t_vars *vars, int x, t_texture *text, t_ray *r)
{
	float		step;
	int			d;
	int			y;

	y = vars->file.h / 2 - r->col_h / 2;
	d = -1;
	step = text->h / (float)r->col_h;
	if (y < 0)
	{
		text->ch = step * abs(y);
		y = 0;
	}
	text->cw = text->w * r->t_x;
	if (text->cw < 0)
		text->cw += text->w;
	while (++d < r->col_h)
	{
		if (y + d < vars->file.h)
			my_mlx_pixel_put(vars->img, x, y + d, (int)*(unsigned int*)\
			(text->img->addr + ((int)text->ch * text->img->line_length\
			+ (int)text->cw * (text->img->bits_per_pixel / 8))));
		text->ch += step;
	}
	text->ch = 0;
}

void			ceiling_place(t_vars *vars, t_file file)
{
	int			color;
	int			x;
	int			y;

	color = create_rgb(file.c.r, file.c.g, file.c.b);
	x = -1;
	y = -1;
	while (++y < file.h / 2)
	{
		while (++x < file.w)
		{
			my_mlx_pixel_put(vars->img, x, y, color);
		}
		x = -1;
	}
}

void			floor_place(t_vars *vars, t_file file)
{
	int			color;
	int			x;
	int			y;

	color = create_rgb(file.f.r, file.f.g, file.f.b);
	x = -1;
	y = file.h / 2 - 1;
	while (++y < file.h)
	{
		while (++x < file.w)
		{
			my_mlx_pixel_put(vars->img, x, y, color);
		}
		x = -1;
	}
}

void			wall_draw_router(t_vars *vars, t_ray *r, int i, double t)
{
	r->gy = r->cy - floor(r->cy + .5);
	r->gx = r->cx - floor(r->cx + .5);
	r->t_x = r->gx;
	if (fabs(r->gy) > fabs(r->gx))
		r->t_x = r->gy;
	r->col_h = vars->file.h / ((t) * cos(r->angle - d_to_r(vars->player.pa)));
	if (r->t_x == r->gx)
	{
		if (r->gy < 0)
			draw_wall(vars, i, &vars->file.so, r);
		else
			draw_wall(vars, i, &vars->file.no, r);
	}
	else
	{
		if (r->gx < 0)
			draw_wall(vars, i, &vars->file.ea, r);
		else
			draw_wall(vars, i, &vars->file.we, r);
	}
}
