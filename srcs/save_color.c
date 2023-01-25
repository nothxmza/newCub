/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:32:26 by jbarette          #+#    #+#             */
/*   Updated: 2022/10/24 14:03:46 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_format_color(char	*color)
{
	char	**split_virgule;
	int		i;

	split_virgule = ft_split(color, ',');
	i = 0;
	while (split_virgule[i])
		i++;
	if (i != 3)
		ft_exit("Les couleurs doivent être au format RGB.");
	i = 0;
	while (split_virgule[i])
	{
		if (!(ft_atoi(split_virgule[i]) >= 0 && ft_atoi(split_virgule[i]) <= 255))
			ft_exit("Les couleurs ont une range comprise entre 0 et 255.");
		i++;
	}
	free_array(split_virgule);
}

char	*create_tab_color(char *line)
{
	char	*tab_color;
	int		i;
	int		k;

	tab_color = malloc(sizeof(char) * ft_strlen(line));
	line = ft_strtrim(line, "\n");
	i = 1;
	k = 0;
	while (line[i])
	{
		while ((line[i] == '\t') || (line[i] == '\v') || (line[i] == '\f') || (line[i] == '\r')
			|| (line[i] == '\n') || (line[i] == ' '))
			i++;
		if (ft_format_color(line[i]))
		{
			if (line[i] == ',' && line[i + 1] == ',')
				i++;
			else
				tab_color[k++] = line[i];
		}
		else
			ft_exit("Uniquement des chiffres dans les couleurs.");
		i++;
	}
	tab_color[k] = '\0';
	return (tab_color);
}

void	save_color(t_params *params, char *line, int id)
{
	char	*tab_color;

	tab_color = ft_strtrim(create_tab_color(line), ",");
	check_format_color(tab_color);
	if (id == 1 && params->floor == NULL)
		params->floor = ft_strdup(tab_color);
	else if (id == 2 && params->ceil == NULL)
		params->ceil = ft_strdup(tab_color);
	else
		ft_exit("Interdit de dupliquer les paramètres.");
	free(tab_color);
}