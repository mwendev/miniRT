/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_planes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:51:56 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/17 14:52:04 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	*normalize_plane(t_plane *plane, float *par)
{
	float	len;

	par[0] = plane->orient[0];
	par[1] = plane->orient[1];
	par[2] = plane->orient[2];
	par[3] = -1 * (par[0] * plane->coord[0] + par[1] * plane->coord[1] + par[2] * plane->coord[2]);
	len = sqrtf(powf(par[0], 2) + powf(par[1], 2) + powf(par[2], 2));
	par[0] = par[0] / len;
	par[1] = par[1] / len;
	par[2] = par[2] / len;
	par[3] = par[3] / len;
	return (par);
}

float	intersection_plane(float *ray, float *origin, t_plane *plane)
{
	float	*a;
	float	t;

	a = malloc(sizeof(float) * 4);
	a = normalize_plane(plane, a);
	t = - (a[0] * origin[0] + a[1] * origin[1] + a[2] * origin[2] + a[3])
			/ (a[0] * ray[0] + a[1] * ray[1] + a[2] * ray[2]);
	free(a);
	if (t <= 0)
		return (0);
	else
		return (t);
}

void	handle_planes(float *ray, t_data *data)
{
	float	t;
	t_plane	*current;
	int		i;

	i = 0;
	current = data->planes;
	while (current != NULL)
	{
		t = intersection_plane(ray, data->camera.coord, current);
		if (t > 0)
		{
			if (check_nearest_point(data, t, i))
			{
				data->obj_counter.shape = 'p';
				mix_ambient(data, data->ambient.rgb, current->rgb,
							data->ambient.ratio);
			}
		}
		current = current->next;
		i++;
	}
}