/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 21:49:54 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/17 13:29:57 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double			step_by_step(t_player *pl, t_map *map, t_ray *r, double t)
{
	if (map_check(map, pl->y - (t + .0001) * r->siny,\
	pl->x - (t + .0001) * r->cosx, '1'))
		return (.00001);
	else if (map_check(map, pl->y - (t + .01) * r->siny, \
	pl->x - (t + .01) * r->cosx, '1'))
		return (.0001);
	else
		return (.01);
}

void			ray_caster(t_vars *vars, t_map *map, t_player *pl)
{
	int			i;
	t_ray		r;
	double		t;

	r.angle = (d_to_r(pl->pa - pl->fov / 2));
	i = -1;
	while (++i < vars->file.w)
	{
		r.cosx = cos(r.angle);
		r.siny = sin(r.angle);
		r.cx = pl->x;
		r.cy = pl->y;
		t = 0;
		while (!map_check(map, (int)r.cy, (int)r.cx, '1'))
		{
			if (map_check(map, (int)r.cy, (int)r.cx, '2'))
				sprite_set_status(vars, &r);
			t += step_by_step(pl, map, &r, t);
			r.cx = pl->x - t * r.cosx;
			r.cy = pl->y - t * r.siny;
		}
		wall_draw_router(vars, &r, i, t);
		vars->deep[i] = t;
		r.angle += pl->rays_angle;
	}
}
