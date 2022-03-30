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

float	distance(float *center, float *origin, float *ray, float t)
{
	float	cross_p[3];
	float	dist;

	cross_p[0] = origin[0] + ray[0] * t;
	cross_p[1] = origin[1] + ray[1] * t;
	cross_p[2] = origin[2] + ray[2] * t;
	dist = sqrtf(powf((center[0] - cross_p[0]), 2)
	+ powf((center[1] - cross_p[1]), 2)
	+ powf((center[2] - cross_p[2]), 2));
	return (dist);
}

float	intersection_cylinder_cap(float *ray, float *origin,
								t_cylinder *cylinder, float offset)
{
	float	*center;
	float	angle;
	float	*a;
	float	v0;
	float	t;

	angle = dot_prod(ray, cylinder->orient);
	if (angle == 0)
		return (0);
	center = malloc(sizeof(float) * 3);
	if (offset == 0)
	{
		center[0] = cylinder->coord[0];
		center[1] = cylinder->coord[1];
		center[2] = cylinder->coord[2];
	}
	else
	{
		center[0] = cylinder->coord[0] + cylinder->orient[0] * cylinder->height;
		center[1] = cylinder->coord[1] + cylinder->orient[1] * cylinder->height;
		center[2] = cylinder->coord[2] + cylinder->orient[2] * cylinder->height;
	}
	a = malloc(sizeof(float) * 4);
	a = normalize_plane(cylinder->orient, cylinder->coord, a);
	v0 = - (a[0] * origin[0] + a[1] * origin[1]
			+ a[2] * origin[2] + a[3]);
	t = intersection_plane(ray, a, v0);
	free(a);
	if (distance(center, origin, ray, t) > (cylinder->diameter / 2))
	{
		free(center);
		return (0);
	}
	free(center);
	return (t);
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
		c[0] = ray[0] * t + origin[0] - cylinder->coord[0];
		c[1] = ray[1] * t + origin[1] - cylinder->coord[1];
		c[2] = ray[2] * t + origin[2] - cylinder->coord[2];
		b = dot_prod(cylinder->orient, c);
		if (b < 0 || b > cylinder->height)
			return (free_return_float(a, 0));
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
		t = intersection_cylinder_cap(ray, data->camera.coord, current, 0);
		if (t > 0)
		{
			if (check_nearest_point(data, t, i))
			{
				data->obj_counter.shape = 'z';
				mix_ambient(data, data->ambient.rgb, current->rgb,
							data->ambient.ratio);
			}
		}
		t = intersection_cylinder_cap(ray, data->camera.coord, current, 1);
		if (t > 0)
		{
			if (check_nearest_point(data, t, i))
			{
				data->obj_counter.shape = 'r';
				mix_ambient(data, data->ambient.rgb, current->rgb,
							data->ambient.ratio);
			}
		}
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
