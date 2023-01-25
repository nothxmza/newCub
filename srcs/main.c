/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeremybarette <jeremybarette@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:12:49 by jbarette          #+#    #+#             */
/*   Updated: 2022/12/28 12:04:27 by jeremybaret      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_params	*params;

	if (argc != 2)
		ft_exit("Vous devez indiquer le chemin de la MAP.");
	params = init_params();
	parsing(params, argv[1]);
    printf("%s %s %s %s %s %s", params->north, params->south, params->west, params->east, params->floor, params->ceil);
	// if (start_game(params))
	// 	ft_exit("Une erreur est survenu lors du lancement de la partie.");
	free_structure(params);
	return (0);
}