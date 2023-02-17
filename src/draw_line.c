/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:39:03 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/02/15 21:05:03 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

double abss(double n)
{
	if (n > 0)
		return (n);
	return (n * (-1));
}

static int get_steps(double dx, double dy)
{
	if (abss(dx) > abss(dy))
		return (abss(dx));
	return round(abss(dy));
}

int is_valid(int x, int y)
{
	if (x < screenWidth && x >= 0 && y < screenHeight && y >= 0)
		return 1;
	return 0;
}
void draw_ray(t_vector *vec, t_vars *vars)
{
	double steps;
	double x;
	double y;
	double ix;
	double iy;

	steps = get_steps(vec->dx, vec->dy);
	if (steps == 0)
		steps = 1;
	// ix = (vec->dx * 24) / steps;
	// iy = (vec->dy * 24) / steps;
	ix = (vec->dx / steps);
	iy = (vec->dy / steps);
	printf("%lf\n", steps);
	
	x = vars->player.pos_p.x;
	y = vars->player.pos_p.y;
	while (is_valid(round(x), round(y)))
	{
		mlx_pixel_put(vars->mlx, vars->win, round(x), round(y), 255 << 8 | 255 << 16);
		x += ix;
		y += iy;
		if (vars->map[((int)round(x) / 24)][(int)round(y) / 24] == 1)
			break;	
	}
}