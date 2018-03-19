/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 10:38:36 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/09 18:23:58 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** ouvre le fichier pour recuperer le nombre de ligne
*/

static void		get_height(char *path, t_map *map)
{
	int		fd;
	char	*tmp;
	size_t	height;

	height = 0;
	fd = open(path, O_RDONLY);
	close_open(fd, "open");
	while (get_next_line(fd, &tmp) > 0)
	{
		height++;
		free(tmp);
	}
	map->height = height;
	close_open(fd, "close");
	if (!height)
		die("Invalid map");
}

static void		get_width(char **tmp, t_map *map)
{
	size_t x;

	x = -1;
	while (tmp[++x])
		;
	if ((map->width > 0 && x != map->width) || x == 0)
		die("Invalid map");
	map->width = x;
}

/*
** remplit le tableau d'int par ligne
** gere egalement l'altitude et la largeur
*/

static void		fill_tab(t_map *map, char *line, size_t y)
{
	char	**tmp;
	size_t	x;

	if (!line)
		return ;
	tmp = ft_strsplit(line, ' ');
	get_width(tmp, map);
	map->tab[y] = (t_point**)malloc(sizeof(t_point*) * map->width);
	set_tile_size(map);
	x = -1;
	while (tmp[++x])
	{
		map->tab[y][x] = (t_point*)malloc(sizeof(t_point));
		map->tab[y][x]->x = x;
		map->tab[y][x]->y = y;
		map->tab[y][x]->z = ft_atoi(tmp[x]);
		free(tmp[x]);
	}
	free(tmp);
}

static void		init_map(t_map *map)
{
	map->tab = (t_point***)malloc(sizeof(t_point**) * map->height);
	map->angle_x = INIT_ANGLE_X;
	map->angle_y = INIT_ANGLE_Y;
	map->angle_z = INIT_ANGLE_Z;
	map->elev_modif = INIT_ELEV;
}

/*
** ouvre le fichier, malloc, rempli et retourne la map
*/

t_map			*get_input(int ac, char **av)
{
	int		fd;
	size_t	y;
	char	*line;
	t_map	*map;

	line = NULL;
	map = NULL;
	if (ac == 2)
	{
		map = (t_map*)ft_memalloc(sizeof(t_map));
		get_height(av[1], map);
		fd = open(av[1], O_RDONLY);
		close_open(fd, "open");
		init_map(map);
		y = 0;
		while (get_next_line(fd, &line) > 0)
		{
			fill_tab(map, line, y);
			y++;
			free(line);
		}
		close_open(fd, "close");
	}
	set_color(map);
	return (map);
}
