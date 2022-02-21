/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:00:26 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/05/28 20:54:08 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*interm_src;
	char	*interm_dest;

	interm_src = (char *)src;
	interm_dest = (char *)dest;
	if ((interm_src != NULL) && (interm_dest != NULL))
	{
		while (n--)
			*interm_dest++ = *interm_src++;
	}
	return (dest);
}
