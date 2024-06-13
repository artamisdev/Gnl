/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacampos <tacampos@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:34:23 by tacampos          #+#    #+#             */
/*   Updated: 2024/06/13 21:11:45 by tacampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean(char *storage, char *buffer)
{
	free(storage);
	free(buffer);
	return (NULL);
}

char	*read_function(int fd, char *storage)
{
	char	*buffer;
	ssize_t	chars_read;
	char	*aux;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (0);
	while (!ft_strchr(storage, '\n'))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
			return (clean(storage, buffer));
		if (chars_read == 0)
			break ;
		buffer[chars_read] = '\0';
		aux = storage;
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (clean(storage, buffer));
		free(aux);
	}
	free(buffer);
	return (storage);
}

static char	*catch_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		++i;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*reload_storage(char *storage)
{
	int		i;
	int		total_len;
	char	*sub;

	i = 0;
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	if (storage[i] == '\n')
		i++;
	total_len = ft_strlen(storage) - i;
	sub = ft_substr(storage, i, total_len);
	free(storage);
	if (!sub)
		return (NULL);
	return (sub);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	storage = read_function(fd, storage);
	if (!storage)
		return (NULL);
	line = catch_line(storage);
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = reload_storage(storage);
	if (!storage || storage[0] == '\0')
	{
		free(storage);
		storage = NULL;
	}
	return (line);
}
