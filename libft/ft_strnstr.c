/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:43:42 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/05/23 20:51:28 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	found_substring(char *haystack, char *needle, size_t j, size_t l)
{
	int	i;

	i = 0;
	while (*(needle + i) != '\0')
	{
		if (*(haystack + i) != *(needle + i))
			return (0);
		i++;
		j++;
		if (j > l)
			return (0);
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*b;
	char	*l;

	b = (char *)big;
	l = (char *)little;
	if (*l == '\0')
		return (b);
	i = 0;
	while ((*(b + i) != '\0') && (i < len))
	{
		if (*(b + i) == *l)
			if (found_substring(b + i, l, i, len))
				return (b + i);
		i++;
	}
	return (0);
}
