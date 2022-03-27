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

void	calc_coeff_sp(float *ray, float *origin, t_sphere *sphere, float *b)
{
	b[0] = 2 * (ray[0] * (origin[0] - sphere->coord[0])
			+ ray[1] * (origin[1] - sphere->coord[1])
			+ ray[2] * (origin[2] - sphere->coord[2]));
	b[1] = powf((origin[0] - sphere->coord[0]), 2)
		+ powf((origin[1] - sphere->coord[1]), 2)
		+ powf((origin[2] - sphere->coord[2]), 2)
		- powf((sphere->diameter / 2), 2);
	b[2] = powf(b[0], 2) - 4 * b[1];
}

float	intersection_sphere(float *ray, float *origin, t_sphere *sphere)
{
	float	*b;
	float	t;

	b = malloc(sizeof(float) * 3);
	calc_coeff_sp(ray, origin, sphere, b);
	if (b[2] > 0)
	{
		t = (-b[0] - sqrtf(b[2])) / 2;
		if (t < 0)
			t = (-b[0] + sqrtf(b[2])) / 2;
		if (t > 0)
		{
			free(b);
			return (t);
		}
	}
	free(b);
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

float	*normal_vector_sp(t_sphere *current, float *intersect)
{
	float	*res;

	res = malloc(sizeof(float) * 3);
	res = vector_two_points(current->coord, intersect, res);
	normalize_vector(res);
	return (res);
}
