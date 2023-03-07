/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:39:03 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/03/07 08:24:37 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

int rgbcolor(int red, int green, int blue)
{
	return red << 16 | green << 8 | blue;
}

t_vector rotate_vector_s(t_vector *a, double teta)
{
	t_vector sum;

	if (teta == 1)
	{
		sum.dx = (a->dx * cos((PI * 5) / 4)) - (a->dy * sin((PI * 5) / 4));
		sum.dy = (a->dx) * sin((PI * 5) / 4) + (a->dy) * cos((PI * 5) / 4);
	}
	else
	{
		sum.dx = (a->dx * cos(-1 * (PI * 5) / 4)) - (a->dy * sin(-1 * (PI * 5) / 4));
		sum.dy = (a->dx) * sin(-1 * (PI * 5) / 4) + (a->dy) * cos(-1 * (PI * 5) / 4);
	}
	return sum;
}
void DDA_ver(int X, int start, int end, t_vars *vars, int color)
{

	for (int i = start; i <= end; i++)
	{
		mlx_pixel_put(vars->mlx, vars->win, X, i, color); // put pixel at (X,Y)
	}
}

void DDA(int X0, int Y0, double m, t_vector *vec, t_vars *vars)
{
	// calculate dx & dy
	int dx = (vec->dx) * m;
	int dy = (vec->dy) * m;

	// calculate steps required for generating pixels
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	// calculate increment in x & y for each steps
	if (steps == 0)
		steps = 1;
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	// Put pixel for each step
	float X = X0;
	float Y = Y0;
	// printf("steps : %d\n", steps);
	for (int i = 0; i <= steps; i++)
	{
		// printf("round(X) : %f\n", round(X));
		mlx_pixel_put(vars->mlx, vars->win, round(X), round(Y), 255 << 8);
		// putpixel(round(X), round(Y),
		//          RED); // put pixel at (X,Y)
		X += Xinc; // increment in x at each step
		Y += Yinc; // increment in y at each step
				   // generation step by step
	}
	if (m != 10)
	{
		X -= Xinc; // increment in x at each step
		Y -= Yinc; // increment in y at each step
		t_vector a = rotate_vector_s(vec, 1);
		DDA(round(X), round(Y), 10, &a, vars);
		a = rotate_vector_s(vec, 0);
		DDA(round(X), round(Y), 10, &a, vars);
	}
}
void fill_image_with_color(void *img_ptr, int color, int width, int height)
{
	int a;
	char *img_data = mlx_get_data_addr(img_ptr, &a, &a, &a);
	int bpp = 32;					// bits per pixel
	int row_size = bpp * width / 8; // size of one row in bytes
	int x, y;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			int offset = y * row_size + x * (bpp / 8);
			img_data[offset] = (color >> 16) & 0xFF;	// red component
			img_data[offset + 1] = (color >> 8) & 0xFF; // green component
			img_data[offset + 2] = color & 0xFF;		// blue component
		}
	}
}

void draw_ray(t_vars *vars)
{
	int x = -1;
	int imagex = 0;
	int imagey = 0;
	int starty = 0;
	int color = 0;
	while (++x < screenWidth)
	{
		double perpWallDist;
		// calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; // x-coordinate in camera space
		double rayDirX = vars->player.vec.dx + vars->player.planeX * cameraX;
		double rayDirY = vars->player.vec.dy + vars->player.planeY * cameraX;
		// which box of the map we're in
		int mapX = (int)(vars->player.pos_p.x);
		int mapY = (int)(vars->player.pos_p.y);

		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// length of ray from one x or y-side to next x or y-side
		// these are derived as:
		// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		// which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
		// where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
		// unlike (dirX, dirY) is not 1, however this does not matter, only the
		// ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		// stepping further below works. So the values can be computed as below.
		//  Division through zero is prevented, even though technically that's not
		//  needed in C++ with IEEE 754 floating point values.
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		// double perpWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; // was there a wall hit?
		int side;	 // was a NS or a EW wall hit?
		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (vars->player.pos_p.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - vars->player.pos_p.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (vars->player.pos_p.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - vars->player.pos_p.y) * deltaDistY;
		}
		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			// mlx_pixel_put(vars->mlx, vars->win, mapX * 24, mapY*24, 255 << 8 | 255 << 16);
			// Check if ray has hit a wall
			// printf("x = %d y = %d\n",mapX , mapY );
			if (vars->map[mapX][mapY] >= 1)
			{
				// mlx_pixel_put(vars->mlx, vars->win, (mapX) * 24, (mapY) * 24, 255 << 16);
				hit = 1;
				// printf("mapx= %d\n", mapY * 24);
				break;
			}
			// printf("end\n");
		}

		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(screenHeight / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		if (imagey == 0)
		{
			imagex = x;
			imagey = drawEnd - drawStart + 1;
			starty = drawStart;
		}
		if (imagey != drawEnd - drawStart + 1 || (x + 1) == screenWidth)
		{
			// printf("drawStart= %d\n", drawStart);
			// printf("drawEnd= %d\n", drawEnd);
			// printf("imgex= %d\n", imagex);
			color++;
			switch (color %  5)
			{
			case 1:
				color = rgbcolor(143, 0, 1);
				break; // red
			case 2:
				color = rgbcolor(143, 174, 1);
				break; // green
			case 3:
				color = rgbcolor(143, 174, 234);
				break; // blue
			case 4:
				color = rgbcolor(255, 255, 255);
				break; // white
			default:
				color = rgbcolor(158, 0, 141);
				break; // yellow
			}
			void *img = mlx_new_image(vars->mlx, x - imagex + 1, imagey);
			fill_image_with_color(img, color, x - imagex + 1, imagey);
			mlx_put_image_to_window(vars->mlx, vars->win, img, imagex, starty);
			imagex = x;
			imagey = drawEnd - drawStart + 1;
			starty = drawStart;
		}
		// DDA_ver(x, drawStart, drawEnd, vars, color);
	}
	// DDA(vars->player.pos_p.x * 24 + screenWidth, vars->player.pos_p.y * 24, 40, &vars->player.vec, vars);
}