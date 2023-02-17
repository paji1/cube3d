/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:01:53 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/02/14 15:34:03 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <Cube3d.h>

t_vector *new_vector(int dx, int dy)
{
	t_vector *vec;



	vec = (t_vector *)malloc(sizeof(t_vector));
	if (!vec)
		return (NULL);
	vec->dx = dx;
	vec->dy = dy;
	return (vec);
}
t_vector new_vector_byvalue(double dx, double dy)
{
	t_vector vec;

	vec.dx = dx;
	vec.dy = dy;
	return (vec);
}

void rotate_vector(t_vars *vars, t_vector *a, double teta)
{
	t_vector sum;

	(void)vars;
	if (teta == 1)
	{
		sum.dx = (a->dx * vars->player.vec.prec.ang_cos) - (a->dy * vars->player.vec.prec.ang_sin);
		sum.dy = (a->dx) * vars->player.vec.prec.ang_sin + (a->dy) * vars->player.vec.prec.ang_cos;
	}
	else
	{
		sum.dx = (a->dx * vars->player.vec.cprec.ang_cos) - (a->dy * vars->player.vec.cprec.ang_sin);
		sum.dy = (a->dx) * vars->player.vec.cprec.ang_sin + (a->dy) * vars->player.vec.cprec.ang_cos;
	}
	a->dx = sum.dx;
	a->dy = sum.dy;
}

t_vector rotate_vector_byteta(t_vars *vars, t_vector *a, double teta)
{
	t_vector sum;

	if (teta == 1)
	{
		sum.dx = (a->dx * vars->player.vec.prec.ang_cos) - (a->dy * vars->player.vec.prec.ang_sin);
		sum.dy = (a->dx) * vars->player.vec.prec.ang_sin + (a->dy) * vars->player.vec.prec.ang_cos;
	}
	else
	{
		sum.dx = (a->dx * vars->player.vec.cprec.ang_cos) - (a->dy * vars->player.vec.cprec.ang_sin);
		sum.dy = (a->dx) * vars->player.vec.cprec.ang_sin + (a->dy) * vars->player.vec.cprec.ang_cos;
	}
	return sum;
}

t_vector add_vector(t_vector a, t_vector b)
{
	t_vector sum;
	
	sum.dx = a.dx + b.dx;
	sum.dy = a.dy + b.dy;
	return sum;
}


void	free_vector(t_vector *vec)
{
	free(vec);
}
