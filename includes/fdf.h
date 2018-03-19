/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:26:49 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/09 12:58:55 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "mlx_keys_macos.h"
# include "math.h"
# include <stdio.h>

# define WINDOW_HEIGHT	600
# define WINDOW_WIDTH	800

# define INIT_ELEV		0.05
# define INIT_ANGLE_X	-0.936
# define INIT_ANGLE_Y	-0.023
# define INIT_ANGLE_Z	-0.372
# define MARGE			10

# define UP_C			0xFFFFFF
# define DOWN_C			0x2ea700
# define MEDIUM_C		0x895F00
# define OCEAN_C		0x002575

typedef struct			s_point
{
	double				x;
	double				y;
	double				z;
	int					color;
}						t_point;

typedef struct			s_rgb
{
	int					a;
	int					r;
	int					g;
	int					b;
}						t_rgb;

typedef struct			s_map
{
	t_point				***tab;
	size_t				height;
	size_t				width;
	double				tile_size;
	double				max;
	double				elev_modif;
	double				angle_x;
	double				angle_y;
	double				angle_z;
}						t_map;

typedef struct			s_img
{
	void				*img_ptr;
	int					*data;
	int					size_l;
	int					bpp;
	int					endian;
}						t_img;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_map				*map;
	t_img				img;
}						t_env;

void					close_open(int fd, char *fc);
void					die(char *msg);
void					mallcheck(void *param);
void					free_all(t_env *env);

void					get_size(char *path, t_map *map);
t_map					*get_input(int ac, char **av);
void					set_world(t_map *map);
void					set_tile_size(t_map *map);
void					set_color(t_map *map);

void					mlx_draw(t_env *env, t_map *map);

int						key_event(int keycode, void *param);

int						to_rgb(int a, int r, int g, int b);
t_rgb					give_rgb(int hex);
int						get_gradient(int ini_color,
int final_color, int i, double nb_pix);
#endif
