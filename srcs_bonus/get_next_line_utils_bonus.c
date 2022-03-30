/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 00:35:47 by mwen              #+#    #+#             */
/*   Updated: 2022/03/14 17:24:57 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

long long	ft_strrlen(char *str)
{
	long long	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmmove(void *dest, const void *src, long long n)
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

char	*ft_strrjoin(char *s1, char *s2)
{
	long long	size;
	char		*both;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strrlen(s1) + ft_strrlen(s2) + 1;
	both = malloc ((size) * sizeof(char));
	if (!both)
		return (NULL);
	ft_memmmove(both, s1, ft_strrlen(s1));
	ft_memmmove(both + ft_strrlen(s1), s2, ft_strrlen(s2));
	both[size - 1] = '\0';
	free(s1);
	return (both);
}
