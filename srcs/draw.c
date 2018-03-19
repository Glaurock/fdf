/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 10:56:44 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/09 13:27:58 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Algorithme de trace de segment de Bresenham
** copy init point :
** tab[0] = x
** tab[1] = y
** difference
** tab[2] = diff x
** tab[3] = diff y
** incrementation verticale / horizontal
** tab[4] = xinc
** tab[5] = yinc
** tab[6] = cumul d'erreur a chaque tour
*/

void	vertical(t_env *env, int tab[7], t_point *ini_point,
t_point *final_point)
{
	int		i;

	tab[6] = tab[3] / 2;
	i = 0;
	while (++i <= tab[3])
	{
		tab[1] += tab[5];
		tab[6] += tab[2];
		if (tab[6] >= tab[3])
		{
			tab[6] -= tab[3];
			tab[0] += tab[4];
		}
		if (tab[1] < WINDOW_HEIGHT && tab[1] > 0
		&& tab[0] < WINDOW_WIDTH && tab[0] > 0)
			env->img.data[tab[1] * WINDOW_WIDTH + tab[0]] =
			get_gradient(ini_point->color, final_point->color, i, tab[3]);
	}
}

void	horizontal(t_env *env, int tab[7], t_point *ini_point,
t_point *final_point)
{
	int		i;

	tab[6] = tab[2] / 2;
	i = 0;
	while (++i <= tab[2])
	{
		tab[0] += tab[4];
		tab[6] += tab[3];
		if (tab[6] >= tab[2])
		{
			tab[6] -= tab[2];
			tab[1] += tab[5];
		}
		if (tab[1] < WINDOW_HEIGHT && tab[1] > 0 && tab[0]
		< WINDOW_WIDTH && tab[0] > 0)
			env->img.data[tab[1] * WINDOW_WIDTH + tab[0]] =
			get_gradient(ini_point->color, final_point->color, i, tab[2]);
	}
}

void	rotate_xyz(t_map *map, t_point *point,
double *coord_x, double *coord_y)
{
	double tab0[3];
	double tab1[3];
	double tab[3];

	tab[2] = point->z * map->elev_modif * map->tile_size;
	tab[0] = (point->x - map->width / 2) * map->tile_size;
	tab[1] = (point->y - map->height / 2) * map->tile_size;
	tab0[0] = tab[0];
	tab0[1] = tab[1] * cos(map->angle_x) + tab[2] * sin(map->angle_x);
	tab0[2] = tab[2] * cos(map->angle_x) + tab[1] * sin(map->angle_x);
	tab1[0] = tab0[0] * cos(map->angle_y) - tab0[2] * sin(map->angle_y);
	tab1[1] = tab0[1];
	tab1[2] = tab0[2] * cos(map->angle_y) + tab0[0] * sin(map->angle_y);
	tab0[0] = tab1[0] * cos(map->angle_z) + tab1[1] * sin(map->angle_z);
	tab0[1] = tab1[1] * cos(map->angle_z) - tab1[0] * sin(map->angle_z);
	*coord_x = tab0[0] + (double)WINDOW_WIDTH / 2;
	*coord_y = tab0[1] + (double)WINDOW_HEIGHT / 2;
}

void	draw_line(t_env *env, t_point *ini_point, t_point *final_point)
{
	int		tab[7];
	double	coord_x;
	double	coord_y;
	double	coord_final_x;
	double	coord_final_y;

	rotate_xyz(env->map, ini_point, &coord_x, &coord_y);
	rotate_xyz(env->map, final_point, &coord_final_x, &coord_final_y);
	tab[0] = floor(coord_x);
	tab[1] = floor(coord_y);
	tab[2] = floor(coord_final_x - coord_x);
	tab[3] = floor(coord_final_y - coord_y);
	tab[4] = (tab[2] > 0) ? 1 : -1;
	tab[5] = (tab[3] > 0) ? 1 : -1;
	tab[2] = abs(tab[2]);
	tab[3] = abs(tab[3]);
	if (tab[1] < WINDOW_HEIGHT && tab[1] > 0 &&
	tab[0] < WINDOW_WIDTH && tab[0] > 0)
		env->img.data[tab[1] * WINDOW_WIDTH + tab[0]] = ini_point->color;
	if (tab[2] > tab[3])
		horizontal(env, tab, ini_point, final_point);
	else
		vertical(env, tab, ini_point, final_point);
}

/*
** fonction d'impression en fonction des points de la map
** appel draw_line qui relie chaque points
*/

void	mlx_draw(t_env *env, t_map *map)
{
	size_t	y;
	size_t	x;

	env->img.img_ptr = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	env->img.data = (int*)mlx_get_data_addr(env->img.img_ptr, &env->img.bpp,
	&env->img.size_l, &env->img.endian);
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (x + 1 < map->width)
				draw_line(env, map->tab[y][x], map->tab[y][x + 1]);
			if (y + 1 < map->height)
				draw_line(env, map->tab[y][x], map->tab[y + 1][x]);
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img.img_ptr, 0, 0);
	mlx_destroy_image(env->mlx, env->img.img_ptr);
}
