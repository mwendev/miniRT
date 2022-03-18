/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:40:11 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/17 14:40:19 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	intersection_sphere(float *ray, float *origin, t_sphere *sphere)
{
	float	b[3];
	float	t;

	b[0] = 2 * (ray[0] * (origin[0] - sphere->coord[0])
				+ ray[1] * (origin[1] - sphere->coord[1])
				+ ray[2] * (origin[2] - sphere->coord[2]));
	b[1] = powf((origin[0] - sphere->coord[0]), 2)
		   + powf((origin[1] - sphere->coord[1]), 2)
		   + powf((origin[2] - sphere->coord[2]), 2)
		   - powf((sphere->diameter / 2), 2);
	b[2] = powf(b[0], 2) - 4 * b[1];
	if (b[2] < 0)
		return (0);
	else
	{
		t = (-b[0] - sqrtf(b[2])) / 2;
		if (t > 0)
			return (t);
		else
		{
			t = (-b[0] + sqrtf(b[2])) / 2;
			if (t > 0)
				return (t);
		}
	}
	return (0);
}

void	handle_spheres(float *ray, t_data *data)
{
	float		t;
	t_sphere	*current;
	int			i;

	i = 0;
	current = data->spheres;
	while (current != NULL)
	{
		t = intersection_sphere(ray, data->camera.coord, current);
		if (t > 0)
		{
			if (check_nearest_point(data, t, i))
			{
				data->obj_counter.shape = 's';
				mix_ambient(data, data->ambient.rgb, current->rgb,
							data->ambient.ratio);
			}
		}
		current = current->next;
		i++;
	}
}

