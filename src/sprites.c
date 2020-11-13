/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 21:55:18 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/19 11:36:43 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			add_sprite(t_spt **spt, int y, int x)
{
	t_spt *spt_new;
	t_spt *res;

	if (!(spt_new = malloc(sizeof(t_spt))))
		error_exit("malloc error");
	spt_new->cy = y;
	spt_new->y = (float)y + .5;
	spt_new->cx = x;
	spt_new->x = (float)x + .5;
	spt_new->status = 0;
	spt_new->t = 0;
	spt_new->next = NULL;
	if (*spt == NULL)
		*spt = spt_new;
	else
	{
		res = *spt;
		while (res->next)
			res = res->next;
		res->next = spt_new;
	}
}

void			sprite_set_status(t_vars *vars, t_ray *r)
{
	t_spt *node;

	node = vars->spt;
	while (node)
	{
		if (node->cy == (int)r->cy && node->cx == (int)r->cx)
		{
			if (!node->status)
			{
				node->status++;
				node->t = sqrt(pow(vars->player.x - node->x, 2)\
				+ pow(vars->player.y - (node->y), 2));
			}
			break ;
		}
		node = node->next;
	}
}

void			draw_sprite(t_vars *vars, int x, int y, t_s_p *s_p)
{
	my_mlx_pixel_put(vars->img, x, y, (int)*(unsigned int*)\
	(vars->file.s.img->addr + ((int)s_p->ch\
	* vars->file.s.img->line_length + (int)s_p->cw\
	* (vars->file.s.img->bits_per_pixel / 8))));
}

void			place_sprite(t_vars *vars, int x, int y, t_s_p *s_p)
{
	int			i;
	int			d;

	s_p->cw = 0;
	s_p->ch = 0;
	s_p->step = vars->file.s.h / (float)s_p->size;
	i = -1;
	d = -1;
	while (++d < s_p->size && x + d < vars->file.w)
	{
		while (++i < s_p->size && y + i < vars->file.h\
		&& y + i > 0 && x + d > 0)
		{
			if (fabs(vars->deep[x + d]) > s_p->t)
				draw_sprite(vars, x + d, y + i, s_p);
			s_p->ch += s_p->step;
		}
		i = -1;
		s_p->ch = 0;
		s_p->cw += s_p->step;
	}
}
