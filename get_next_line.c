/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:54:09 by alirola-          #+#    #+#             */
/*   Updated: 2023/09/22 19:21:03 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static char	*clean_buffer(char *str)
{
	int		i;
	int		j;
	char	*str_res;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	str_res = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!str_res)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i] != '\0')
		str_res[j++] = str[i++];
	str_res[j] = '\0';
	return (free(str), str_res);
}

static char	*get_actual_line(char *str)
{
	char	*str_res;
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	str_res = ft_calloc((i + 1), sizeof(char));
	if (!str_res)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		str_res[i] = str[i];
		i++;
	}
	if (str[i] != '\0' && str[i] == '\n')
		str_res[i++] = '\n';
	str_res[i] = '\0';
	return (str_res);
}

static char	*join(char *str, char *buffer)
{
	char	*r;

	r = ft_strjoin(str, buffer);
	if (!r)
		return (NULL);
	return (r);
}

static char	*read_fd(int fd, char *str)
{
	char	*temp;
	int		read_char;

	temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!temp)
		return (NULL);
	read_char = 1;
	while (read_char > 0 && !ft_strchr_mod(temp, '\n'))
	{
		read_char = read(fd, temp, BUFFER_SIZE);
		if (read_char < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[read_char] = '\0';
		str = join(str, temp);
		if (!str)
			return (free(str), free(temp), NULL);
	}
	return (free(temp), str);
}

char	*get_next_line(int fd)
{
	static char		*str;
	char			*actual_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (str != NULL)
		{
			free(str);
			str = NULL;
		}
		return (NULL);
	}
	str = read_fd(fd, str);
	if (!str)
		return (free(str), str = NULL, NULL);
	actual_line = get_actual_line(str);
	if (!actual_line)
		return (free(str), str = NULL, NULL);
	str = clean_buffer(str);
	if (!str)
		return (free(str), str = NULL, actual_line);
	return (actual_line);
}
/*
int	main(void)
{
	int		fichero;
	char	*line;

	fichero = open("test.txt", O_RDONLY);
	line = get_next_line(fichero);
	while (line != NULL)
	{
		printf("%s", line);
		line = get_next_line (fichero);
	}
	printf("\n");
	close(fichero);
	free(line);
}
*/