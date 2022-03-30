/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:45:58 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/20 19:46:11 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	calc_coeff_cyl(t_cylinder *cylinder, float *a, float *origin,
					float *ray)
{
	float	*w;
	float	*h;

	h = malloc(sizeof(float) * 3);
	h[0] = cylinder->orient[0];
	h[1] = cylinder->orient[1];
	h[2] = cylinder->orient[2];
	normalize_vector(h);
	w = malloc(sizeof(float) * 3);
	w = vector_two_points(cylinder->coord, origin, w);
	a[0] = 1 - powf(dot_prod(ray, h), 2);
	a[1] = 2 * (dot_prod(ray, w) - dot_prod(ray, h) * dot_prod(w, h));
	a[2] = dot_prod(w, w) - powf(dot_prod(w, h), 2)
		- powf((cylinder->diameter) / 2, 2);
	free(w);
	free(h);
	a[3] = powf(a[1], 2) - 4 * a[0] * a[2];
}

float	intersection_cylinder_body(float *ray, float *origin,
								t_cylinder *cylinder)
{
	float	*a;
	float	t[2];
	float	c[3];

	a = malloc(sizeof(float) * 4);
	calc_coeff_cyl(cylinder, a, origin, ray);
	if (a[3] < 0)
		return (free_return_float(a, 0));
	else
	{
		t[0] = (-a[1] - sqrtf(a[3])) / (2 * a[0]);
		if (t[0] < 0)
		{
			t[0] = (-a[1] + sqrtf(a[3])) / (2 * a[0]);
			if (t[0] < 0)
				return (free_return_float(a, 0));
		}
		c[0] = ray[0] * t[0] + origin[0] - cylinder->coord[0];
		c[1] = ray[1] * t[0] + origin[1] - cylinder->coord[1];
		c[2] = ray[2] * t[0] + origin[2] - cylinder->coord[2];
		t[1] = dot_prod(cylinder->orient, c);
		if (t[1] < 0 || t[1] > cylinder->height)
			return (free_return_float(a, 0));
	}
	return (free_return_float(a, t[0]));
}

void	check_and_mix(char shape, t_data *data, int i, t_cylinder *current)
{
	if (data->t > 0)
	{
		if (check_nearest_point(data, data->t, i))
		{
			data->obj_counter.shape = shape;
			mix_ambient(data, data->ambient.rgb, current->rgb,
				data->ambient.ratio);
		}
	}
}

void	handle_cylinders(float *ray, t_data *data)
{
	t_cylinder	*current;
	int			i;

	i = 0;
	current = data->cylinders;
	while (current != NULL)
	{
		data->t = intersection_cylinder_body(ray, data->camera.coord, current);
		check_and_mix('y', data, i, current);
		data->t = intersection_cylinder_cap(ray, data->camera.coord, current,
				0);
		check_and_mix('z', data, i, current);
		data->t = intersection_cylinder_cap(ray, data->camera.coord, current,
				1);
		check_and_mix('z', data, i, current);
		current = current->next;
		i++;
	}
}

float	*normal_vector_cyl_body(t_cylinder *current, float *intersect)
{
	float	*w;
	float	*res;
	float	*interm;

	w = malloc(sizeof(float) * 3);
	res = malloc(sizeof(float) * 3);
	w = vector_two_points(intersect, current->coord, w);
	interm = malloc(sizeof(float) * 3);
	cross_product(current->orient, w, interm);
	cross_product(current->orient, interm, res);
	free(w);
	free(interm);
	return (res);
}
