/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 20:50:19 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/05 18:30:09 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n, int i)
{
	if (n / 10 != 0)
		i = count_digits(n / 10, ++i);
	return (i);
}

static char	*number_to_string(long n, char *str)
{
	char	a;

	if (n / 10 != 0)
		str = number_to_string(n / 10, str);
	a = n % 10 + '0';
	*str++ = a;
	return (str);
}

/*
** i[0] - counter, i[1] - negative. function too long (26 lines).
*/

static char	*allocate(int	*i)
{
	char	*result;

	if (i[1])
		result = (char *)malloc(sizeof(char) * (i[0] + 2));
	else
		result = (char *)malloc(sizeof(char) * (i[0] + 1));
	if (!result)
		return (0);
	return (result);
}

char	*ft_itoa(int n)
{
	int		i[2];
	char	*result;
	char	*base;
	long	nb;

	i[0] = 0;
	nb = (long)n;
	if (nb < 0)
	{
		i[1] = 1;
		nb *= -1;
	}
	else
		i[1] = 0;
	i[0] = count_digits(nb, i[0]) + 1;
	result = allocate(i);
	if (result == NULL)
		return (0);
	base = result;
	if (i[1])
		*result++ = '-';
	number_to_string(nb, result);
	*(result + i[0]) = '\0';
	return (base);
}
