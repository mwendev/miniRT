/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:32:30 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/05 18:08:22 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	found_char(char str, const char *set)
{
	while (*set)
		if (*set++ == str)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*temp_s1;
	unsigned int	len;
	char			*new_str;
	unsigned int	final_len;

	temp_s1 = (char *)s1;
	len = ft_strlen(temp_s1);
	while (len && found_char(*(temp_s1 + len - 1), set))
		len--;
	while (len && found_char(*temp_s1, set))
	{
		temp_s1++;
		len--;
	}
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (0);
	final_len = len;
	while (len--)
		*new_str++ = *temp_s1++;
	*new_str = '\0';
	return (new_str - final_len);
}
