/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:47:27 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/05/21 15:36:41 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** first while loop is to move d pointer to the end of the string and to check
** if buffer is <= len(dst). Puttin n-- in the while loop and reassigning n
** after the loop saves us 2 lines of code (norminette)
** If buffer size is smaller than len(dst), return value will be buffer size
** + len(src), i.e. smaller than len(dst) + len(src)
** Next loop till the end of src. If buffer is < len(src) + len(dst), do not 
** copy anything after size - 1 (n = 1), but loop till the end of src, to get 
** the correct return value.
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;
	size_t		len_d;

	n = size;
	d = dst;
	s = src;
	while (n-- != 0 && *d != '\0')
		d++;
	len_d = d - dst;
	n = size - len_d;
	if (n == 0)
		return (len_d + ft_strlen(s));
	while (*s != '\0')
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (len_d + (s - src));
}
