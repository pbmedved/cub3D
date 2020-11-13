/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 09:05:10 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/18 09:05:20 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct		s_data{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct		s_action{
	int				move_f;
	int				move_d;
	int				move_l;
	int				move_r;
	int				turn_l;
	int				turn_r;
}					t_action;

typedef struct		s_spt{
	float			y;
	int				cy;
	float			x;
	int				cx;
	int				status;
	double			t;
	struct s_spt	*next;
}					t_spt;

typedef struct		s_color{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_texture{
	t_data			*img;
	int				h;
	int				w;
	float			ch;
	float			cw;
}					t_texture;

typedef struct		s_map{
	int				map_h;
	int				map_w;
	char			**map;
}					t_map;

typedef struct		s_file{
	int				w;
	int				h;
	t_map			map;
	t_texture		no;
	t_texture		so;
	t_texture		we;
	t_texture		ea;
	t_texture		s;
	t_color			f;
	t_color			c;
	int				map_start;
}					t_file;

typedef struct		s_player{
	int				fov;
	int				pa;
	float			y;
	float			x;
	float			fov_rad;
	float			rays_angle;
}					t_player;

typedef struct		s_act_m{
	double			stepx;
	double			stepy;
}					t_act_m;
typedef struct		s_vars{
	void			*mlx;
	void			*mlx_win;
	t_data			*img;
	t_file			file;
	t_player		player;
	t_spt			*spt;
	double			*deep;
	int				save_mode;
	t_action		action;
}					t_vars;

typedef struct		s_ray{
	float			cx;
	float			cy;
	int				col_h;
	double			angle;
	float			t_x;
	double			cosx;
	double			siny;
	double			gy;
	double			gx;
}					t_ray;

typedef struct		s_s_p{
	float			step;
	int				size;
	double			t;
	float			cw;
	float			ch;
}					t_s_p;

#endif
