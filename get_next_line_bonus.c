/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:48:01 by alirola-          #+#    #+#             */
/*   Updated: 2023/10/02 15:40:08 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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
	static char		*str[1024];
	char			*actual_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (str[fd] != NULL)
		{
			free(str[fd]);
			str[fd] = NULL;
		}
		return (NULL);
	}
	str[fd] = read_fd(fd, str[fd]);
	if (!str[fd])
		return (free(str[fd]), str[fd] = NULL, NULL);
	actual_line = get_actual_line(str[fd]);
	if (!actual_line)
		return (free(str[fd]), str[fd] = NULL, NULL);
	str[fd] = clean_buffer (str[fd]);
	if (!str[fd])
		return (free(str[fd]), str[fd] = NULL, actual_line);
	return (actual_line);
}
/*
int main ()
{
	int fichero;
	int	fichero2;
	int	fichero3;
	char *linef1;
	char *linef2;
	char *linef3;	

	fichero = open("test.txt", O_RDONLY);
	fichero2 = open("test2.txt", 0);
	fichero3 = open("vacio", 0);
	linef1 = get_next_line(fichero);
	while (linef1 != NULL)
	{
		printf("%s", linef1);
		linef1 = get_next_line(fichero);
	}
	printf("\n");
	linef2 = get_next_line(fichero2);
	while (linef2 != NULL)
	{
		printf("%s", linef2);
		linef2 = get_next_line(fichero2);
	}
	printf("\n");
	linef3 = get_next_line(fichero3);
	while (linef3 != NULL)
	{
		printf("%s", linef3);
		linef3 = get_next_line(fichero3);
	}
	close(fichero);
	close(fichero2);
	close(fichero3);
	free(linef1);
	free(linef2);
	free(linef3);
}
*/