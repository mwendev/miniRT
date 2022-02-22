/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:22:38 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/05 17:48:28 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*temp_s;
	char	*new_str;
	char	*temp_new_str;

	temp_s = (char *)s;
	new_str = malloc(ft_strlen(s) + 1);
	if (!new_str)
		return (0);
	temp_new_str = new_str;
	*temp_new_str = '\0';
	if (*s == '\0')
		return (new_str);
	while (*temp_s != '\0')
		*temp_new_str++ = *temp_s++;
	*temp_new_str = '\0';
	return (new_str);
}
