/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 11:49:13 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/09 09:51:00 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** applique une couleur en fonction de l'altitude du point
*/

static void		apply_color(t_map *map)
{
	size_t	x;
	size_t	y;
	double	ret;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			ret = (map->tab[y][x]->z / map->max);
			if (ret <= 0.33)
				map->tab[y][x]->color = DOWN_C;
			else if (ret >= 0.66)
				map->tab[y][x]->color = UP_C;
			else
				map->tab[y][x]->color = MEDIUM_C;
			if (map->tab[y][x]->z <= 0)
				map->tab[y][x]->color = OCEAN_C;
		}
	}
}

void			set_color(t_map *map)
{
	size_t x;
	size_t y;

	map->max = map->tab[0][0]->z;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->tab[y][x]->z > map->max)
				map->max = map->tab[y][x]->z;
		}
	}
	apply_color(map);
}
