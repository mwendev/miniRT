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

#include "minirt.h"

void	calc_coeff_cyl(t_cylinder *cylinder, float *a, float *origin, float *ray)
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
	float	t;
	float	b;
	float	c[3];

	a = malloc(sizeof(float) * 4);
	calc_coeff_cyl(cylinder, a, origin, ray);
	if (a[3] < 0)
		return (free_return_float(a, 0));
	else
	{
		t = (-a[1] - sqrtf(a[3])) / (2 * a[0]);
		if (t < 0)
		{
			t = (-a[1] + sqrtf(a[3])) / (2 * a[0]);
			if (t < 0)
				return (free_return_float(a, 0));
		}
//		c[0] = ray[0] * t - cylinder->coord[0];
//		c[1] = ray[1] * t - cylinder->coord[1];
//		c[2] = ray[2] * t - cylinder->coord[2];
//		b = dot_prod(cylinder->orient, c);
//		if (b < 0 || b > cylinder->height)
//			return (free_return_float(a, 0));
	}
	return (free_return_float(a, t));
}

void	handle_cylinders(float *ray, t_data *data)
{
	float		t;
	t_cylinder	*current;
	int			i;

	i = 0;
	current = data->cylinders;
	while (current != NULL)
	{
		t = intersection_cylinder_body(ray, data->camera.coord, current);
		if (t > 0)
		{
			if (check_nearest_point(data, t, i))
			{
				data->obj_counter.shape = 'y';
				mix_ambient(data, data->ambient.rgb, current->rgb,
					data->ambient.ratio);
			}
		}
		current = current->next;
		i++;
	}
}

float	*normal_vector_cyl(t_cylinder *current, float *intersect)
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
