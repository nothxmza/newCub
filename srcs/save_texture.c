/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeremybarette <jeremybarette@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:32:26 by jbarette          #+#    #+#             */
/*   Updated: 2022/12/28 22:23:20 by jeremybaret      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*cpy_texture(char	*line)
{
	char		*texture_trim;
	char		*texture_w_id;
	int			i;
	int			k;

	i = 2;
	k = 0;
	while (line[i] != '.')
		i++;
	texture_trim = ft_strtrim(line, "\n");
	texture_w_id = malloc(sizeof(char) * ft_strlen(texture_trim));
	while (texture_trim[i])
		texture_w_id[k++] = texture_trim[i++];
	texture_w_id[k] = '\0';
	free(texture_trim);
	return (texture_w_id);
}

void	save_texture(t_params *params, char *line, int id)
{
	char		*texture_w_id;
	
	texture_w_id = ft_strtrim(cpy_texture(line), " ");
	if (open(texture_w_id, O_RDONLY) == -1)
		ft_exit("Une ou des textures sont introuvables.");
	if (id == 1 && params->north == NULL)
		params->north = ft_strdup(texture_w_id);
	else if (id == 2 && params->south == NULL)
		params->south = ft_strdup(texture_w_id);
	else if (id == 3 && params->west == NULL)
		params->west = ft_strdup(texture_w_id);
	else if (id == 4 && params->east == NULL)
		params->east = ft_strdup(texture_w_id);
	else
		ft_exit("Interdit de dupliquer les paramètres.");
	free(texture_w_id);
}