/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:28:19 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/06 14:30:46 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		close_open(int fd, char *fc)
{
	if (ft_strcmp(fc, "close") == 0)
	{
		if (fd == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}
	}
	else if (ft_strcmp(fc, "open") == 0)
	{
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
	}
}

void		die(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void		mallcheck(void *param)
{
	if (param == NULL)
		die("Malloc error");
}
