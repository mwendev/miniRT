/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:02:50 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/05 18:06:00 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*temp_s1;
	char			*temp_s2;
	char			*new_str;
	unsigned int	len;

	temp_s1 = (char *)s1;
	temp_s2 = (char *)s2;
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (0);
	while (*temp_s1)
		*new_str++ = *temp_s1++;
	while (*temp_s2)
		*new_str++ = *temp_s2++;
	*new_str = '\0';
	return (new_str - len);
}
