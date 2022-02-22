/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 20:33:01 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/05/21 21:40:57 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*interm_s1;
	unsigned char	*interm_s2;

	i = 0;
	interm_s1 = (unsigned char *)s1;
	interm_s2 = (unsigned char *)s2;
	while (i < n && (*interm_s1 != '\0' || *interm_s2 != '\0'))
	{
		if (*interm_s2 != *interm_s1)
			return (*interm_s1 - *interm_s2);
		interm_s1++;
		interm_s2++;
		i++;
	}
	return (0);
}
