/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:00:26 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/05/28 21:08:33 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*interm_src;
	char	*interm_dest;

	interm_src = (char *)src;
	interm_dest = (char *)dest;
	if ((interm_src != NULL) && (interm_dest != NULL))
	{
		while (n--)
		{
			*interm_dest++ = *interm_src++;
			if (*(interm_dest - 1) == (unsigned char)c)
				return (interm_dest);
		}
	}
	return (0);
}
