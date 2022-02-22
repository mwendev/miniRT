/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 01:31:28 by mwen              #+#    #+#             */
/*   Updated: 2021/11/22 11:54:45 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	*get_min_max(t_fdf *data)
{
	int	*z_m;
	int	x;
	int	y;

	z_m = malloc(2 * sizeof(int));
	if (!z_m)
		terminate(ERR_INIT_COLOR, data);
	z_m[0] = 0;
	z_m[1] = 0;
	y = -1;
	while (++y < data->map->hgt)
	{
		x = -1;
		while (++x < data->map->wid)
		{
			if (data->map->p[y][x].z < z_m[0])
				z_m[0] = data->map->p[y][x].z;
			else if (data->map->p[y][x].z > z_m[1])
				z_m[1] = data->map->p[y][x].z;
		}
	}
	return (z_m);
}

void	assign_color(t_fdf *data)
{
	double	percentage;
	int		*z_m;
	int		xy[2];

	z_m = get_min_max(data);
	xy[0] = -1;
	while (++xy[0] < data->map->hgt)
	{
		xy[1] = -1;
		while (++xy[1] < data->map->wid)
		{
			if (data->map->p[xy[0]][xy[1]].color == GROUND_COL)
			{
				percentage = percent(z_m[0], z_m[1],
						data->map->p[xy[0]][xy[1]].z);
				if (percentage > 0 && percentage < 0.4)
					data->map->p[xy[0]][xy[1]].color = SLOP_COL;
				else if (percentage > 0 && percentage < 0.8)
					data->map->p[xy[0]][xy[1]].color = SLOPP_COL;
				else if (percentage > 0)
					data->map->p[xy[0]][xy[1]].color = PEAK_COL;
			}
		}
	}
	free(z_m);
}
