/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 00:35:47 by mwen              #+#    #+#             */
/*   Updated: 2021/10/27 14:22:29 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

long long	ft_strlen_ngl(char *str)
{
	long long	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmove(void *dest, const void *src, long long n)
{
	long long	i;

	if (!dest || !src)
		return (NULL);
	if (src > dest)
	{
		i = 0;
		while (i < n)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			*(unsigned char *)(dest + i - 1) = *(unsigned char *)(src + i - 1);
			i--;
		}
	}
	return (dest);
}

char	*ft_strjoin_ngl(char *s1, char *s2)
{
	long long	size;
	char		*both;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen_ngl(s1) + ft_strlen_ngl(s2) + 1;
	both = malloc ((size) * sizeof(char));
	if (!both)
		return (NULL);
	ft_memmove(both, s1, ft_strlen_ngl(s1));
	ft_memmove(both + ft_strlen_ngl(s1), s2, ft_strlen_ngl(s2));
	both[size - 1] = '\0';
	free(s1);
	return (both);
}
