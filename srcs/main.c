/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeremybarette <jeremybarette@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:12:49 by jbarette          #+#    #+#             */
/*   Updated: 2023/01/25 13:06:41 by jeremybaret      ###   ########.fr       */
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
    if (start_game(params))
	    ft_exit("Une erreur est survenu lors du lancement de la partie.");
	free_structure(params);
	return (0);
}