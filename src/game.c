/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:25:25 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/18 09:55:19 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			prepare_img(t_vars *vars)
{
	if (!(vars->img->img = mlx_new_image(vars->mlx,\
	vars->file.w, vars->file.h)))
		error_exit("img error");
	if (!(vars->img->addr = mlx_get_data_addr(vars->img->img,\
	&vars->img->bits_per_pixel, &vars->img->line_length,\
	&vars->img->endian)))
		error_exit("img addr error");
}

int				frame_render(t_vars *vars)
{
	turn_pa(&vars->player, &vars->action);
	action_apply(&vars->player, &vars->action, &vars->file.map);
	floor_place(vars, vars->file);
	ceiling_place(vars, vars->file);
	fix_pa(&vars->player);
	ray_caster(vars, &vars->file.map, &vars->player);
	sprite_sort(vars);
	if (vars->save_mode)
		export_bmp(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img->img, 0, 0);
	mlx_do_sync(vars->mlx);
	return (1);
}

void			add_deep(t_vars *vars)
{
	if (!(vars->deep = malloc(sizeof(double) * vars->file.w)))
		error_exit("malloc error");
}

static int		cub_exit(int n)
{
	exit(n);
}

void			game(t_vars *vars)
{
	vars->action = (t_action){0, 0, 0, 0, 0, 0};
	resolution_check(&vars->file, vars);
	add_deep(vars);
	set_player(vars, &vars->player, &vars->file.map);
	if (!vars->save_mode)
		if (!(vars->mlx_win = mlx_new_window(vars->mlx, vars->file.w,\
		vars->file.h, "cub3d")))
			error_exit("new window");
	prepare_img(vars);
	frame_render(vars);
	mlx_hook(vars->mlx_win, 2, 0, act_on, vars);
	mlx_hook(vars->mlx_win, 3, 0, act_off, vars);
	mlx_loop_hook(vars->mlx, frame_render, vars);
	mlx_hook(vars->mlx_win, 17, 1Lu << 17u, cub_exit, 0);
	mlx_loop(vars->mlx);
}
