/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:41:43 by alirola-          #+#    #+#             */
/*   Updated: 2023/05/30 18:34:14 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret_str;
	size_t	len;
	int		i;
	int		a;

	i = 0;
	a = 0;
	len = ((size_t)ft_strlen(s1) + (size_t)ft_strlen(s2));
	ret_str = (char *)malloc(((len + 1) * sizeof(char)));
	if (!ret_str)
		return (NULL);
	while (s1[i])
	{
		ret_str[i] = s1[i];
		i++;
	}
	while (s2[a])
	{
		ret_str[i + a] = s2[a];
		a++;
	}
	ret_str[i + a] = '\0';
	return (ret_str);
}

void	ft_bezero_full(void *s, size_t n)
{
	unsigned char	*b;
	size_t			i;

	i = 0;
	b = (unsigned char *)s;
	while (i < n)
	{
		b[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_bezero_full(ptr, count * size);
	return (ptr);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strchr_mod(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}
