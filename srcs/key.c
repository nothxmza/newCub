/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:36:17 by jbarette          #+#    #+#             */
/*   Updated: 2022/11/18 15:46:33 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	event_press(int keycode, t_params *params)
{
	if (keycode == 13)
	{
		if (params->map[params->pos_x + (int)params->dirX * (int)params->moveSpeed][params->pos_y] == '0')
			params->pos_x += params->dirX * params->moveSpeed;
		if (params->map[params->pos_x][params->pos_y + (int)params->dirY * (int)params->moveSpeed] == '0')
			params->pos_y += params->dirY * params->moveSpeed;
	}
	if (keycode == 1)
	{
		if(params->map[params->pos_x - (int)params->dirX * (int)params->moveSpeed][params->pos_y] == '0')
			params->pos_x -= params->dirX * params->moveSpeed;
		if(params->map[params->pos_x][params->pos_y - (int)params->dirY * (int)params->moveSpeed] == '0')
			params->pos_y -= params->dirY * params->moveSpeed;
	}
	if (keycode == 2)
	{
		double oldDirX = params->dirX;
		params->dirX = params->dirX * cos(-params->rotSpeed) - params->dirY * sin(-params->rotSpeed);
		params->dirY = oldDirX * sin(-params->rotSpeed) + params->dirY * cos(-params->rotSpeed);
		double oldPlaneX = params->planeX;
		params->planeX = params->planeX * cos(-params->rotSpeed) - params->planeY * sin(-params->rotSpeed);
		params->planeY = oldPlaneX * sin(-params->rotSpeed) + params->planeY * cos(-params->rotSpeed);
	}
	if (keycode == 0)
	{
		double oldDirX = params->dirX;
		params->dirX = params->dirX * cos(params->rotSpeed) - params->dirY * sin(params->rotSpeed);
		params->dirY = oldDirX * sin(params->rotSpeed) + params->dirY * cos(params->rotSpeed);
		double oldPlaneX = params->planeX;
		params->planeX = params->planeX * cos(params->rotSpeed) - params->planeY * sin(params->rotSpeed);
		params->planeY = oldPlaneX * sin(params->rotSpeed) + params->planeY * cos(params->rotSpeed);
	}
	// if (keycode == 1)
	// {
	// 	params->pos_y += 1;
	// 	if (params->map[params->pos_y][params->pos_x] == '1')
	// 		params->pos_y -= 1;
	// }
	// if (keycode == 0)
	// {
	// 	params->pos_x -= 1;
	// 	if (params->map[params->pos_y][params->pos_x] == '1')
	// 		params->pos_x += 1;
	// }
	// if (keycode == 2)
	// {
	// 	params->pos_x += 1;
	// 	if (params->map[params->pos_y][params->pos_x] == '1')
	// 		params->pos_x -= 1;
	// }
	if (keycode == 53)
		close_win(params);
	//mlx_destroy_image(params->mlx, params->img.img);
	return (0);
}