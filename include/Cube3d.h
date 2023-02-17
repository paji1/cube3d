#ifndef Cube3d_H
# define Cube3d_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "types.h"
# include <math.h>
# define PI 3.141592654




// function
int init(t_vars *_vars);

// utils
void	print_map_on_terminal(int map[mapWidth][mapHeight]);

// mlx_hook 
void game_hooks(t_vars *vars);

// points
void init_point(t_point *_point, int x, int y);
void point_set_x(t_point *_point, int x);
void point_set_y(t_point *_point, int y);

// draw line (DDA)

// vectors 
t_vector	new_vector_byvalue(double dx, double dy);
t_vector	add_vector(t_vector a, t_vector b);
t_vector	rotate_vector_byteta(t_vars *vars, t_vector *a, double teta);
void		rotate_vector(t_vars *vars, t_vector *a, double teta);
// draw map
void	draw_wall(t_vars *vars);
// exit_game
int	exit_game(t_vars *vars);

#endif