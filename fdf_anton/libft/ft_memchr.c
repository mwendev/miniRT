/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:50:06 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/05 16:59:55 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*interm_s;

	interm_s = (char *)s;
	while (n--)
	{
		if (*interm_s == c)
			return (interm_s);
		else
			interm_s++;
	}
	return (0);
}
