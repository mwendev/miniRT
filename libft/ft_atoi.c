/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 21:46:39 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/05/28 21:32:11 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}

static int	ft_issign(char c)
{
	if (c == '-')
		return (-1);
	else if (c == '+')
		return (1);
	return (0);
}

static int	initialize_string(char *str, int *number, int *sign)
{
	if (ft_isspace(*str))
		;
	else if (*str == '\0')
		return (0);
	else if (ft_isdigit(*str))
		*number = *str - '0';
	else if (ft_issign(*str))
		*sign = ft_issign(*str);
	else
		return (0);
	return (1);
}

static int	atoi_loop(char *str, int *number, int *sign)
{
	while (*str++ != '\0')
	{
		if (ft_isspace(*str))
		{
			if (!ft_isspace(*(str - 1)))
				return (*number * *sign);
		}
		else if (ft_issign(*str))
		{
			if (ft_isspace(*(str - 1)))
				*sign = ft_issign(*str);
			else if (ft_isdigit(*(str - 1)))
				return (*number * *sign);
			else
				return (0);
		}
		else if (ft_isdigit(*str))
			*number = *number * 10 + *str - '0';
		else
			return (*number * *sign);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		number;
	int		sign;
	char	*str;

	str = (char *)nptr;
	number = 0;
	sign = 1;
	if (!initialize_string(str, &number, &sign))
		return (0);
	return (atoi_loop(str, &number, &sign));
}
