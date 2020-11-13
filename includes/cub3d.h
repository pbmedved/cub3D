/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:17:55 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/19 11:36:06 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "structs.h"

# define COLLISION_OFFSET 4
# define PLAYER_SPEED 0.15

/*
** color.c
*/

int		create_rgb(int r, int g, int b);
void	check_color(t_color a);

/*
** error.c
*/

void	error_exit(char *s);

/*
** draw.c
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_wall(t_vars *vars, int x, t_texture *text, t_ray *r);
void	ceiling_place(t_vars *vars, t_file file);
void	floor_place(t_vars *vars, t_file file);
void	wall_draw_router(t_vars *vars, t_ray *r, int i, double t);

/*
** file.c
*/

void	set_file(t_file *file);
void	check_file(t_file *file);
void	create_config_file(char *s, t_file *file, t_vars *vars);
void	resolution_check(t_file *file, t_vars *vars);

/*
** game.c
*/

void	prepare_img(t_vars *vars);
int		frame_render(t_vars *vars);
void	add_deep(t_vars *vars);
void	game(t_vars *vars);

/*
** map.c map1.c
*/

char	**map_alloc(size_t h);
void	map_size_calc(char *line, t_file *file, int fd);
void	create_map(int fd, t_map *map, t_file *file);
void	parse_map(int fd, t_file *file, t_map *map);
void	check_map_zero(t_map *map, int i, int d);
void	check_map(t_map *map);
int		map_check(t_map *m, int y, int x, char c);

/*
** move.c
*/

void	check_action(t_player *pl, t_map *m, t_act_m *act_m);
void	action_apply(t_player *pl, t_action *act, t_map *m);
void	turn_pa(t_player *pl, t_action *act);
int		act_on(int key, t_vars *vars);
int		act_off(int key, t_vars *vars);

/*
** parse.c parse1.c
*/

void	parse_file(int fd, t_file *file, t_vars *vars);
void	parse_resolution(char *line, t_file *file);
void	parse_color(char *line, t_color *color);
void	parse_file(int fd, t_file *file, t_vars *vars);
void	parse_redirect_t(char *s, t_file *file, t_vars *vars);
void	parse_redirect_c(char *s, t_file *file);

/*
** player.c
*/

void	fix_pa(t_player *pl);
void	set_player_coord(t_vars *vars, t_player *player, t_map *map);
void	set_player(t_vars *vars, t_player *player, t_map *map);
float	get_pa(char c);

/*
** raycast.c
*/

double	step_by_step(t_player *pl, t_map *map, t_ray *r, double t);
void	ray_caster(t_vars *vars, t_map *map, t_player *pl);

/*
** screensh.c
*/

void	fill_bmp(char **data, t_vars *vars);
void	header_bmp(char **data, t_vars *vars);
void	export_bmp(t_vars *vars);

/*
** sprites.c sprites1.c
*/

void	add_sprite(t_spt **spt, int y, int x);
void	sprite_set_status(t_vars *vars, t_ray *r);
void	place_sprite(t_vars *vars, int x, int y, t_s_p *s_p);
void	draw_sprite(t_vars *vars, int x, int y, t_s_p *s_p);
void	sprite_calc(t_vars *vars, t_player *pl, t_spt *spt);
void	sprite_sort(t_vars *vars);

/*
** texture.c
*/

void	parse_texture(char *s, t_texture *texture, t_vars *vars);
void	check_textures(t_file *file);

/*
** utils.c utils1.c
*/

int		get_next_line(char **line, int fd, int i);
int		ft_simple_atoi(char *store);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
char	*ft_strdup_size(const char *str, size_t size);
char	*ft_strchr(const char *str, int ch);
double	d_to_r(int d);
#endif
