/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:47:21 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/05 17:58:12 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	char	*new_str;
	char	*temp;

	new_str = malloc(len + 1);
	if (!new_str)
		return (0);
	temp = new_str;
	*new_str = '\0';
	p = (char *) s;
	if (*p == '\0')
		return (new_str);
	while (start--)
		if (*++p == '\0')
			return (new_str);
	while ((*p != '\0') && (len > 0))
	{
		*temp++ = *p++;
		len--;
	}
	*temp = '\0';
	return (new_str);
}
