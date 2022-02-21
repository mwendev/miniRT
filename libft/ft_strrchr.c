/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:25:24 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/05 17:25:40 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p != '\0')
		p++;
	if (*p == c)
		return (p);
	while (p != s)
	{
		if (*p == c)
			return (p);
		p--;
	}
	if (*p == c)
		return (p);
	return (0);
}
