/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:57:15 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/02/15 21:18:30 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

int tabx[4] = {-1, 0, 1, 0};
int taby[4] = {0, 1, 0, -1};

void draw_ray(t_vector *vec, t_vars *vars);

int key_handle(int keycode, t_vars *vars)
{
	static int der;
	mlx_clear_window(vars->mlx, vars->win);
	draw_wall(vars);
	if (keycode == 65363)
	{
		rotate_vector(vars, &vars->player.vec, 1);
		draw_ray(&vars->player.vec, vars);
		t_vector vec = vars->player.vec;
		for (int i = 0; i < 30; i++)
		{
			vec = rotate_vector_byteta(vars, &vec, -1);
			draw_ray(&vec, vars);
		}
		vec = vars->player.vec;
		for (int i = 0; i < 30; i++)
		{
			vec = rotate_vector_byteta(vars, &vec, 1);
			draw_ray(&vec, vars);
		}
	}
	if (keycode == 65361)
	{
		rotate_vector(vars, &vars->player.vec, -1);
		draw_ray(&vars->player.vec, vars);
		t_vector vec = vars->player.vec;
		for (int i = 0; i < 30; i++)
		{
			vec = rotate_vector_byteta(vars, &vec, -1);
			draw_ray(&vec, vars);
		}
		vec = vars->player.vec;
		for (int i = 0; i < 30; i++)
		{
			vec = rotate_vector_byteta(vars, &vec, 1);
			draw_ray(&vec, vars);
		}
	}
	if (keycode == 65362)
	{
		if (der == -1)
		{
			vars->player.vec.dx *= -1;
			vars->player.vec.dy *= -1;
		}
		vars->player.pos_p.x += ((vars->player.vec.dx * 24) * der) ;
		vars->player.pos_p.y += ((vars->player.vec.dy * 24) * der) ;
		if (vars->player.pos_p.y >= screenHeight || vars->player.pos_p.y < screenHeight)
			return 0;
		if (vars->player.pos_p.x >= screenWidth || vars->player.pos_p.x < screenWidth)
			return 0;
		der = 1;
		draw_ray(&vars->player.vec, vars);
		t_vector vec = vars->player.vec;
		for (int i = 0; i < 60; i++)
		{
			vec = rotate_vector_byteta(vars, &vec, -1);
			draw_ray(&vec, vars);
		}
		vec = vars->player.vec;
		for (int i = 0; i < 60; i++)
		{
			vec = rotate_vector_byteta(vars, &vec, 1);
			draw_ray(&vec, vars);
		}
	}
	if (keycode == 65364)
	{
		if (der == 1)
		{
			vars->player.vec.dx *= -1;
			vars->player.vec.dy *= -1;
		}
		vars->player.pos_p.x -= ((vars->player.vec.dx * 24) * der) ;
		vars->player.pos_p.y -= ((vars->player.vec.dy * 24) * der) ;
	
		der = -1;
		draw_ray(&vars->player.vec, vars);
		t_vector vec = vars->player.vec;
		for (int i = 0; i < 30; i++)
		{
			vec = rotate_vector_byteta(vars, &vec, -1);
			draw_ray(&vec, vars);
		}
		vec = vars->player.vec;
		for (int i = 0; i < 30; i++)
		{
			vec = rotate_vector_byteta(vars, &vec, 1);
			draw_ray(&vec, vars);
		}
	}
	// printf("%d\n", keycode);
	return 0;
}
void game_hooks(t_vars *vars)
{
	t_point a;
	t_point b;
	// print_map_on_terminal(vars->map);
	mlx_hook(vars->win, 2, 1L << 0, key_handle, vars);
	mlx_hook(vars->win, 17, 0, exit_game, vars);

	init_point(&a, 0, 0);
	init_point(&b, 120, 120);

	draw_wall(vars);

	draw_ray(&vars->player.vec, vars);
	t_vector vec = vars->player.vec;
	for (int i = 0; i < 3; i++)
	{
		vec = rotate_vector_byteta(vars, &vec, -1);
		draw_ray(&vec, vars);
	}
	vec = vars->player.vec;
	for (int i = 0; i < 3; i++)
	{
		vec = rotate_vector_byteta(vars, &vec, 1);
		draw_ray(&vec, vars);
	}
	// draw_line(a , b, vars);
	mlx_loop(vars->mlx);
}