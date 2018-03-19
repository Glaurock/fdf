/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 10:48:43 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/09 12:40:45 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		rotate_modif(int keycode, t_env *env)
{
	if (keycode == KEY_W)
		env->map->angle_x -= 5 * (double)M_PI / 180;
	else if (keycode == KEY_S)
		env->map->angle_x += 5 * (double)M_PI / 180;
	else if (keycode == KEY_Q)
		env->map->angle_z -= 5 * (double)M_PI / 180;
	else if (keycode == KEY_E)
		env->map->angle_z += 5 * (double)M_PI / 180;
	else if (keycode == KEY_A)
		env->map->angle_y -= 5 * (double)M_PI / 180;
	else if (keycode == KEY_D)
		env->map->angle_y += 5 * (double)M_PI / 180;
	mlx_draw(env, env->map);
}

static void		size_modif(int keycode, t_env *env)
{
	if (keycode == KEY_PAD_ADD)
		env->map->elev_modif *= 1.1;
	else if (keycode == KEY_PAD_SUB)
		env->map->elev_modif /= 1.1;
	else if (keycode == KEY_RIGHT)
		env->map->tile_size += 0.5;
	else if (keycode == KEY_LEFT)
	{
		env->map->tile_size -= 0.5;
		if (env->map->tile_size < 0)
			env->map->tile_size = 0;
	}
	mlx_draw(env, env->map);
}

int				key_event(int keycode, void *param)
{
	t_env *env;

	env = (t_env*)param;
	if (keycode == KEY_ESCAPE)
	{
		free_all(env);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KEY_RIGHT || keycode == KEY_LEFT ||
	keycode == KEY_PAD_ADD || keycode == KEY_PAD_SUB)
		size_modif(keycode, env);
	else if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_Q
	|| keycode == KEY_E || keycode == KEY_A || keycode == KEY_D)
		rotate_modif(keycode, env);
	return (0);
}
