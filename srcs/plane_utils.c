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

float	intersection_plane(t_data *data, float *ray, float *a, float v0)
{
	float	t;
	float	vd;

	data->plane_norm_koeff = 1;
	vd = (a[0] * ray[0] + a[1] * ray[1] + a[2] * ray[2]);
	if (vd > 0)
		data->plane_norm_koeff = -1;
	t = v0 / vd;
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
	float	*a;
	float	v0;

	i = 0;
	a = malloc(sizeof(float) * 4);
	current = data->planes;
	while (current != NULL)
	{
		a = normalize_plane(current, a);
		v0 = - (a[0] * data->camera.coord[0] + a[1] * data->camera.coord[1] + a[2] * data->camera.coord[2] + a[3]);
		t = intersection_plane(data, ray, a, v0);
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
	free(a);
}