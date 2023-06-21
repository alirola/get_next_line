/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:54:09 by alirola-          #+#    #+#             */
/*   Updated: 2023/06/21 14:55:46 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
