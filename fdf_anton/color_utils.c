/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:18:29 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/10/15 15:18:31 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	scan_base(const char *base, char needle)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == needle)
			break ;
		i++;
	}
	return (i);
}

int	hex_to_int(char *hex_num)
{
	int		i;
	int		j;
	int		power;
	double	result;

	i = (int)ft_strlen(hex_num) - 1;
	result = 0;
	power = 0;
	while (hex_num[i] != 'x' && i >= 0)
	{
		j = scan_base("0123456789ABCDEF", hex_num[i]);
		if (j == 16)
			j = scan_base("0123456789abcdef", hex_num[i]);
		if (j == 16)
			j = 15;
		result += j * pow(16, power);
		power++;
		i--;
	}
	return ((int)result);
}

int	**allocate_image(int h, int w)
{
	int	i;
	int	**image;

	i = -1;
	image = malloc(h * sizeof(int *));
	while (++i < h)
		image[i] = malloc(w * sizeof(int));
	return (image);
}
