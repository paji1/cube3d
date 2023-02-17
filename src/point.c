/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:34:29 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/02/13 18:10:39 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

void init_point(t_point *_point, int x, int y)
{
	_point->x = x;
	_point->y = y;
}

void point_set_x(t_point *_point, int x)
{
	_point->x = x;
}

void point_set_y(t_point *_point, int y)
{
	_point->y = y;
}

t_point *new_point(int x, int y)
{
	t_point *p;

	p = malloc(sizeof(t_point));
	if (!p)
		return (NULL);
	p->x = x;
	p->y = y;
	return (p);
}
