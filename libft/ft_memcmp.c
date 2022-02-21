/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:01:56 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/05 16:31:32 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*interm_s1;
	unsigned char	*interm_s2;

	interm_s1 = (unsigned char *)s1;
	interm_s2 = (unsigned char *)s2;
	if (interm_s1 == interm_s2)
		return (0);
	while (n--)
	{
		if (*interm_s1 != *interm_s2)
			return (*interm_s1 - *interm_s2);
		else
		{
			interm_s1++;
			interm_s2++;
		}
	}
	return (0);
}
