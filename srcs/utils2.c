/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 11:27:18 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/09 09:47:31 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** recupere la distance entre chaque point la plus grande possible
** pour que l'image rentre dans la fenetre
*/

void		set_tile_size(t_map *map)
{
	double	test_width;
	double	test_height;

	test_width = 1;
	test_height = 1;
	while (test_width * map->width * 1.5 < WINDOW_WIDTH - MARGE)
		test_width += 0.5;
	while (test_height * map->height * 1.5 < WINDOW_HEIGHT - MARGE)
		test_height += 0.5;
	map->tile_size = test_width <= test_height ?
	test_width - 0.5 : test_height - 0.5;
}
