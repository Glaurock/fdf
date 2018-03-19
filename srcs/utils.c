/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 10:39:53 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/09 09:50:02 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_all(t_env *env)
{
	size_t	y;
	size_t	x;
	t_map	*map;

	map = env->map;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->tab[y][x])
				free(map->tab[y][x]);
		}
		if (map->tab[y])
			free(map->tab[y]);
	}
	if (map->tab)
		free(map->tab);
	if (map)
		free(map);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env)
		free(env);
}
