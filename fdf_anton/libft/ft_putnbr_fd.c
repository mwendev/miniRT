/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 15:35:36 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/05/20 21:41:04 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	output_nbr(long n, int fd)
{
	char	a;

	if (n / 10 != 0)
	{
		output_nbr(n / 10, fd);
	}
	a = n % 10 + '0';
	ft_putchar_fd(a, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = (long)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	output_nbr(nb, fd);
}
