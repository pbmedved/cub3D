/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 16:51:37 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/17 15:19:24 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_vars			*add_vars(void)
{
	t_vars *vars;

	if (!(vars = malloc(sizeof(t_vars))))
		error_exit("malloc error");
	if (!(vars->img = malloc(sizeof(t_data))))
		error_exit("malloc error");
	vars->spt = NULL;
	set_file(&vars->file);
	vars->save_mode = 0;
	vars->file.no.img = NULL;
	vars->file.we.img = NULL;
	vars->file.ea.img = NULL;
	vars->file.so.img = NULL;
	vars->file.s.img = NULL;
	return (vars);
}

void			safe_mode_on(t_vars *vars, char *argv)
{
	int i;

	i = -1;
	while (++i < 6 && argv)
	{
		if (argv[i] != "--save"[i])
			error_exit("bad param");
	}
	vars->save_mode = 1;
}

int				main(int argc, char **argv)
{
	t_vars *vars;

	vars = add_vars();
	if (argc == 1)
		error_exit("No map");
	if (argc == 3)
		safe_mode_on(vars, argv[2]);
	if (argc > 3)
		error_exit("argc > 3");
	vars->mlx = mlx_init();
	create_config_file(argv[1], &vars->file, vars);
	game(vars);
	exit(0);
}
