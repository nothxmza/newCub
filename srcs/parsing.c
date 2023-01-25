/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:31:44 by jbarette          #+#    #+#             */
/*   Updated: 2022/10/25 15:11:52 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing(t_params *params, char *file)
{
	check_extension(file);
	read_file(params, file);
	isempty_options(params);
	parser_map(params);
}

void	check_extension(char *file)
{
	int	size;

	size = ft_strlen(file);
	if (!(file[size - 1] == 'b' && file[size - 2] == 'u' && file[size - 3] == 'c' && file[size - 4] == '.'))
		ft_exit("L'extension du fichier est incorrect.");
	if (open(file, O_RDONLY) == -1)
		ft_exit("La carte est introuvable.");
}

void	isempty_options(t_params *params)
{
	if (params->east == NULL \
		|| params->north == NULL \
		|| params->south == NULL \
		|| params->west == NULL)
		ft_exit("Des textures sont manquantes dans la map.");
	if (params->ceil == NULL || params->floor == NULL)
		ft_exit("Des couleurs sont manquantes dans la map.");
}
