/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 05:29:11 by jeremybaret       #+#    #+#             */
/*   Updated: 2022/11/07 22:52:43 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    find_letter(t_params *params)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < params->nbr_lines)
    {
        while (x < ft_strlen(params->map[y]))
        {
			if (params->map[y][x] != '0' && params->map[y][x] != '1' && params->map[y][x] != 'S' \
				&& params->map[y][x] != 'N' && params->map[y][x] != 'W' && params->map[y][x] != 'E')
                ft_exit("Des caractères incorrectes sont dans la map.");
            x++;
        }
        x = 0;
        y++;
    }
}

void    save_position(t_params *params)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < params->nbr_lines)
    {
        while (x < ft_strlen(params->map[y]))
        {
            if (params->map[y][x] == 'S' || params->map[y][x] == 'N' \
				|| params->map[y][x] == 'W' || params->map[y][x] == 'E')
            {
                if (!params->pos)
				{
                    params->pos = params->map[y][x];
					params->pos_x = x;
					params->pos_y = y;
				}
                else
                    ft_exit("Une seule position doit être indiqué pour le joueur.");
            }
            x++;
        }
        x = 0;
        y++;
    }
    if (!params->pos)
        ft_exit("Une position est requise pour le joueur.");
}

void    find_space(t_params *params)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < params->nbr_lines)
    {
        while (x < ft_strlen(params->map[y]))
        {
            if (params->map[y][x] == ' ')
                params->map[y][x] = '1';
            x++;
        }
        x = 0;
        y++;
    }
}

void    find_wall_first_line(t_params *params)
{
    int x;

    x = 0;
    while (x < ft_strlen(params->map[0]))
    {
        if (params->map[0][x] != '1')
            ft_exit("Uniquement des murs pour la 1ère ligne de la MAP.");
        x++;
    }
    x = 0;
    while (x < ft_strlen(params->map[params->nbr_lines - 1]))
    {
        if (params->map[params->nbr_lines - 1][x] != '1')
            ft_exit("Uniquement des murs pour la dernière ligne de la MAP.");
        x++;
    }
}

void    find_wall(t_params *params)
{
    int y;

    y = 0;
    while (y < params->nbr_lines)
    {
        if (params->map[y][0] != '1' || params->map[y][ft_strlen(params->map[y]) - 1] != '1')
            ft_exit("La carte doit être entourée de mur.");
        y++;
    }
}

void    parser_map(t_params *params)
{
    save_position(params);
    find_space(params);
	find_letter(params);
    find_wall_first_line(params);
    find_wall(params);
}