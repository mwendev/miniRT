/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:06:47 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/05 16:39:09 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** first loop: if size > len(src), src will be copied completely into dst and  
** n > 0; if size = len(src), src will be copied completely into dst, except of
** termination 0, and n = 0; if size < len(src), src will not be completely 
** copied into dst and n = 0. We subtract 1 from n before loop to account for 
** termination 0.
** second loop: if the dst is not terminated (n = 0), we terminate it and loop
** over the rest of the src, to get it length.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char		*s;
	size_t			n;

	s = src;
	n = size;
	if (n != 0)
	{
		n--;
		while (n != 0)
		{
			*dst++ = *s;
			n--;
			if (*s == '\0')
				break ;
			s++;
		}
	}
	if (n == 0)
	{
		if (size != 0)
			*dst = '\0';
		while (*s != '\0')
			s++;
	}
	return (s - src);
}
