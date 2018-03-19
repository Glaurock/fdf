/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 09:49:31 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/09 13:11:43 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		to_rgb(int a, int r, int g, int b)
{
	return ((((a > 0xff) ? 0xff : a) << 24) |
			(((r > 0xff) ? 0xff : r) << 16) |
			(((g > 0xff) ? 0xff : g) << 8) |
			((b > 0xff) ? 0xff : b));
}

t_rgb	give_rgb(int hex)
{
	t_rgb color;

	color.a = (hex >> 24) & 0xff;
	color.r = (hex >> 16) & 0xff;
	color.g = (hex >> 8) & 0xff;
	color.b = hex & 0xff;
	return (color);
}

int		get_gradient(int ini_color, int final_color, int i, double nb_pix)
{
	t_rgb		ini_rgb;
	t_rgb		final_rgb;
	double		inc_r;
	double		inc_g;
	double		inc_b;

	if (ini_color == final_color)
		return (ini_color);
	ini_rgb = give_rgb(ini_color);
	final_rgb = give_rgb(final_color);
	inc_r = (double)(final_rgb.r - ini_rgb.r) / nb_pix;
	inc_g = (double)(final_rgb.g - ini_rgb.g) / nb_pix;
	inc_b = (double)(final_rgb.b - ini_rgb.b) / nb_pix;
	return (to_rgb(0, (int)(ini_rgb.r + i * inc_r), (int)(ini_rgb.g +
	i * inc_g), (int)(ini_rgb.b + i * inc_b)));
}
