#ifndef TYPES_H
#define TYPES_H


#define mapWidth 24
#define mapHeight 24
#define screenWidth 576
#define screenHeight 576

typedef struct s_tframe
{
	double time;
	double oldtime;
} t_tframe;

typedef struct s_point
{
	double x;
	double y;
}t_point;

typedef struct s_prec
{
	double ang_cos;
	double ang_sin;
}t_prec;

typedef struct s_vector
{
	double dx;
	double dy;
	double angle;
	double cangle;
	t_prec prec;
	t_prec cprec;
} t_vector;

typedef struct s_pl
{
	t_point		pos_p;
	t_vector	vec;
	double		planeX;
	double		planeY;
} t_pl;

typedef struct s_img
{
	void *wall;
}t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		imgs;
	t_pl		player;
	t_tframe	times;
	int			map[mapWidth][mapHeight];
} t_vars;
#endif