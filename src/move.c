/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:24:06 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/18 08:59:08 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				act_on(int key, t_vars *vars)
{
	if (key == 53)
		exit(0);
	if (key == 124)
		vars->action.turn_l = 1;
	if (key == 123)
		vars->action.turn_r = 1;
	if (key == 13)
		vars->action.move_f = 1;
	if (key == 1)
		vars->action.move_d = 1;
	if (key == 0)
		vars->action.move_l = 1;
	if (key == 2)
		vars->action.move_r = 1;
	return (1);
}

int				act_off(int key, t_vars *vars)
{
	if (key == 53)
		exit(0);
	if (key == 124)
		vars->action.turn_l = 0;
	if (key == 123)
		vars->action.turn_r = 0;
	if (key == 13)
		vars->action.move_f = 0;
	if (key == 1)
		vars->action.move_d = 0;
	if (key == 0)
		vars->action.move_l = 0;
	if (key == 2)
		vars->action.move_r = 0;
	return (1);
}

void			turn_pa(t_player *pl, t_action *act)
{
	if (act->turn_l)
		pl->pa += 2;
	if (act->turn_r)
		pl->pa -= 2;
}

void			check_action(t_player *pl, t_map *m, t_act_m *act_m)
{
	if (!map_check(m, pl->y + act_m->stepy * COLLISION_OFFSET,\
	pl->x + act_m->stepx * COLLISION_OFFSET, '1'))
	{
		pl->y += act_m->stepy;
		pl->x += act_m->stepx;
	}
}

void			action_apply(t_player *pl, t_action *act, t_map *m)
{
	t_act_m		act_m;

	act_m = (t_act_m){0, 0};
	if (act->move_f)
	{
		act_m.stepy -= sin(d_to_r(pl->pa)) * PLAYER_SPEED;
		act_m.stepx -= cos(d_to_r(pl->pa)) * PLAYER_SPEED;
	}
	if (act->move_d)
	{
		act_m.stepy += sin(d_to_r(pl->pa)) * PLAYER_SPEED;
		act_m.stepx += cos(d_to_r(pl->pa)) * PLAYER_SPEED;
	}
	if (act->move_l)
	{
		act_m.stepy -= sin(d_to_r(pl->pa) - M_PI / 2) * PLAYER_SPEED;
		act_m.stepx -= cos(d_to_r(pl->pa) - M_PI / 2) * PLAYER_SPEED;
	}
	if (act->move_r)
	{
		act_m.stepy -= sin(d_to_r(pl->pa) + M_PI / 2) * PLAYER_SPEED;
		act_m.stepx -= cos(d_to_r(pl->pa) + M_PI / 2) * PLAYER_SPEED;
	}
	check_action(pl, m, &act_m);
}
