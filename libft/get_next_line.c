/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:52:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/10/17 16:03:06 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_strchr_line(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	send_line(char *buffer, char **buffer_reminder, int l, char	**rtn)
{
	int		i;
	char	*temp;

	i = ft_strchr_line(buffer, '\n');
	if (i < l)
	{
		if (*buffer_reminder)
		{
			temp = ft_substr(buffer, i + 1, (l - i - 1));
			free(*buffer_reminder);
			*buffer_reminder = temp;
		}
		else if (buffer[i + 1] != 0)
			*buffer_reminder = ft_substr(buffer, i + 1, (l - i - 1));
	}
	buffer[i + 1] = 0;
	if (!(*rtn))
		*rtn = ft_strdup(buffer);
	else
	{	
		temp = ft_strjoin(*rtn, buffer);
		free(*rtn);
		*rtn = temp;
	}
}

int	get_line(char *buffer, char **buffer_reminder, int l, char **rtn)
{
	int		i;
	char	*temp;

	buffer[l] = 0;
	i = ft_strchr_line(buffer, '\n');
	if (i > -1)
	{
		send_line(buffer, buffer_reminder, l, rtn);
		return (1);
	}
	else
	{
		if (!*rtn)
			*rtn = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(*rtn, buffer);
			free(*rtn);
			*rtn = temp;
		}
		return (0);
	}
	return (0);
}

int	check_reminder(char **buffer_reminder, char **rtn)
{
	int		i;
	char	*temp;
	int		size;

	size = ft_strlen(*buffer_reminder);
	i = ft_strchr_line(*buffer_reminder, '\n');
	if (i > -1)
	{
		if (i < size - 1)
		{
			*rtn = ft_substr(*buffer_reminder, 0, i + 1);
			temp = ft_substr(*buffer_reminder, i + 1, (size - i - 1));
			free(*buffer_reminder);
			*buffer_reminder = temp;
			return (1);
		}
		*rtn = *buffer_reminder;
		*buffer_reminder = NULL;
		return (1);
	}
	temp = ft_strjoin("", *buffer_reminder);
	free(*buffer_reminder);
	*buffer_reminder = NULL;
	*rtn = temp;
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*buffer_reminder;
	int			l;
	char		*rtn;

	rtn = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer_reminder && check_reminder(&buffer_reminder, &rtn))
		return (rtn);
	buffer = malloc(BUFFER_SIZE + 1);
	l = read(fd, buffer, BUFFER_SIZE);
	while (l > 0)
	{
		if (get_line(buffer, &buffer_reminder, l, &rtn))
		{
			free(buffer);
			return (rtn);
		}
		l = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (rtn);
}