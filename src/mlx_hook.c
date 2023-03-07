/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:57:15 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/03/07 07:38:30 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"


void draw_ray(t_vars *vars);

# define RIGHT 65363
# define LEFT 65361
# define DOWN 65364
# define UP 65362
int key_handle(int keycode, t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	if (keycode == LEFT)
		rotate_vector(vars, &vars->player.vec, 1);
	else if (keycode == RIGHT)
		rotate_vector(vars, &vars->player.vec, -1);
	else if (keycode == UP)
	{
		double checkx = vars->player.pos_p.x + (vars->player.vec.dx) * 0.12;
		if (vars->map[(int)checkx][(int)vars->player.pos_p.y] == 0)
			vars->player.pos_p.x = checkx;
		double checky = vars->player.pos_p.y + (vars->player.vec.dy) * 0.12;
		if (vars->map[(int)vars->player.pos_p.x][(int)checky] == 0)
			vars->player.pos_p.y = checky;
		
	}
	else if (keycode == DOWN)
	{
		double checkx = vars->player.pos_p.x - (vars->player.vec.dx) * 0.12;
		if (vars->map[(int)checkx][(int)vars->player.pos_p.y] == 0)
			vars->player.pos_p.x = checkx;
		double checky = vars->player.pos_p.y - (vars->player.vec.dy) * 0.12;
		if (vars->map[(int)vars->player.pos_p.x][(int)checky] == 0)
			vars->player.pos_p.y = checky;
		
	}
	// draw_wall(vars);
	draw_ray(vars);
	(void)vars;
	return 0;
}
void game_hooks(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, key_handle, vars);
	mlx_hook(vars->win, 17, 0, exit_game, vars);
	// draw_wall(vars);
	draw_ray(vars);
	mlx_loop(vars->mlx);
}