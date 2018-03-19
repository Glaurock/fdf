/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:26:17 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/09 09:42:01 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** errors check on malloc
*/

int			main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		die("FdF: usage: pass a map as argument");
	mallcheck(env = (t_env*)malloc(sizeof(t_env)));
	env->map = get_input(argc, argv);
	mallcheck(env->mlx = mlx_init());
	mallcheck(env->win = mlx_new_window(env->mlx,
	WINDOW_WIDTH, WINDOW_HEIGHT, "FdF"));
	mlx_draw(env, env->map);
	mlx_key_hook(env->win, key_event, env);
	mlx_loop(env->mlx);
	free_all(env);
	return (0);
}
