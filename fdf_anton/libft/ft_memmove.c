/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:20:40 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/05/20 11:48:03 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Because we are not allowed to use malloc here, we change direction of
** switching characters if destination is further in the memory than source
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*interm_src;
	char	*interm_dest;

	interm_src = (char *)src;
	interm_dest = (char *)dest;
	if ((interm_src != NULL) && (interm_dest != NULL))
	{
		if (dest < src)
			while (n--)
				*interm_dest++ = *interm_src++;
		else
		{
			while (n > 0)
			{
				*(interm_dest + n - 1) = *(interm_src + n - 1);
				n--;
			}
		}
	}
	return (dest);
}
