/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:34:16 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/17 13:22:03 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float			get_pa(char c)
{
	if (c == 'N')
		return (90);
	if (c == 'S')
		return (270);
	if (c == 'W')
		return (0);
	return (180);
}

void			fix_pa(t_player *pl)
{
	if (pl->pa > 360)
		pl->pa -= 360;
	if (pl->pa < 0)
		pl->pa += 360;
}

void			set_player_coord(t_vars *vars, t_player *player, t_map *map)
{
	int			i;
	int			d;

	i = 0;
	d = 0;
	while (map->map[i])
	{
		while (map->map[i][d])
		{
			if (ft_strchr("NSWE", map->map[i][d]))
			{
				player->pa = get_pa(map->map[i][d]);
				player->x = d + .5;
				player->y = i + .5;
			}
			else if (map->map[i][d] == '2')
				add_sprite(&vars->spt, i, d);
			d++;
		}
		d = 0;
		i++;
	}
}

void			set_player(t_vars *vars, t_player *player, t_map *map)
{
	set_player_coord(vars, player, map);
	player->fov = 60;
	player->fov_rad = player->fov * (M_PI / 180);
	player->rays_angle = player->fov_rad / vars->file.w;
}
