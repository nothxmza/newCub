/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeremybarette <jeremybarette@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:05:25 by jbarette          #+#    #+#             */
/*   Updated: 2023/01/25 14:19:15 by jeremybaret      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_image(t_params *params)
{
	params->img.img = mlx_new_image(params->mlx, WidthScreen, HeightScreen);
	params->img.addr = mlx_get_data_addr(params->img.img, &params->img.bits_per_pixel, &params->img.line_length, &params->img.endian);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void verLine(int x, int drawStart, int drawEnd, t_params *params)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(&params->img, x, drawStart, 0xFFFFFF);
		drawStart++;
	}
}

int	draw(t_params *params)
{
	clock_t start = 0;
	clock_t end;
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	int	x = 0;

	while (x < WidthScreen)
	{
		double cameraX = 2 * x / (double)WidthScreen - 1; //x-coordinate in camera space
		double rayPosX = params->pos_x;
		double rayPosY = params->pos_y;
		double rayDirX = params->dirX + params->planeX * cameraX;
		double rayDirY = params->dirY + params->planeY * cameraX;
		int mapX = (int)rayPosX;
		int mapY = (int)rayPosY;
		double sideDistX;
		double sideDistY;
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;
		int stepX;
		int stepY;
		int hit = 0; //was there a wall hit?
		int side = 0; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}

		while (hit == 0)
		{
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
			if (params->map[mapX][mapY] == '1')
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist =  (sideDistY - deltaDistY);
		int lineHeight = (int)(HeightScreen / perpWallDist);
		int drawStart = -lineHeight / 2 + HeightScreen / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HeightScreen / 2;
		if (drawEnd >= HeightScreen)
			drawEnd = HeightScreen - 1;
		verLine(x, drawStart, drawEnd, params);
		x++;
	}
	end = start;
	start = clock();
	/*oldTime = time;
	time = getTicks();
	double frameTime = (time - oldTime) / 1000.0;
	print(1.0 / frameTime);
	redraw();
	cls();*/
	mlx_put_image_to_window(params->mlx, params->mlx_win, params->img.img, 0, 0);
	params->moveSpeed = ((start - end) / CLOCKS_PER_SEC) * 5.0;
	params->rotSpeed = ((start - end) / CLOCKS_PER_SEC) * 3.0;
	return (0);
}

int	start_game(t_params *params)
{
	params->mlx = mlx_init();
	params->mlx_win = mlx_new_window(params->mlx, WidthScreen, HeightScreen, "Hello World!");
	create_image(params);
	mlx_loop_hook(params->mlx, &draw, params);
	mlx_hook(params->mlx_win, 2, 0, &event_press, params);
	mlx_hook(params->mlx_win, 17, 0, &close_win, NULL);
	mlx_loop(params->mlx);
	return (0);
}