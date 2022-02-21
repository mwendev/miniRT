/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:04:29 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/10/16 17:04:46 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_distance(int x1, double x2, int y1, double y2)
{
	return (ft_round(sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2))));
}

int	ft_interpolate(int p1, int p2, int k, int n)
{
	return (ft_round((p2 - p1) * k / n + p1));
}

int	arr_len(char **arr)
{
	int	res;

	res = 0;
	while (arr[res])
		res++;
	return (res);
}

void	emergency_exit(t_window *win, int j, char **arr)
{
	int	i;
	int	k;

	i = -1;
	while (++i < j)
	{
		free(win->heights[i]);
		k = -1;
		while (++k < win->width)
			free(win->char_colors[i][k]);
		free(win->char_colors[i]);
	}
	free(win->heights);
	free(win->char_colors);
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	perror("map file error! \n");
	exit(-1);
}
