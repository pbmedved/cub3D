/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:19:56 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/16 12:46:26 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			sprite_sort(t_vars *vars)
{
	double		max;
	t_spt		*node;
	t_spt		*res;
	t_spt		*final;

	res = vars->spt;
	while (res)
	{
		max = 0;
		final = vars->spt;
		node = vars->spt;
		while (node)
		{
			if (node->status)
				max = max < node->t ? node->t : max;
			node = node->next;
		}
		while (final)
		{
			if (final->status && final->t == max)
				sprite_calc(vars, &vars->player, final);
			final = final->next;
		}
		res = res->next;
	}
}

void			sprite_calc(t_vars *vars, t_player *pl, t_spt *spt)
{
	double		sa;
	t_s_p		s_p;
	int			offset;

	sa = atan2(pl->y - spt->y, pl->x - spt->x);
	while (sa - d_to_r(pl->pa) > M_PI)
		sa -= 2 * M_PI;
	while (sa - d_to_r(pl->pa) < -M_PI)
		sa += 2 * M_PI;
	s_p.size = (vars->file.h / spt->t / 2) >= (vars->file.w / spt->t / 2)\
	? vars->file.w / spt->t / 2 : vars->file.h / spt->t / 2;
	s_p.size = s_p.size < vars->file.h ? s_p.size : vars->file.h;
	s_p.t = spt->t;
	offset = vars->file.w / 2 - (d_to_r(pl->pa) - sa)\
	* vars->file.w - s_p.size / 2;
	place_sprite(vars, offset, (vars->file.h - s_p.size) / 2, &s_p);
	spt->status = 0;
}
