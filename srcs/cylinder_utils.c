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

float	intersection_cylinder(float *ray, float *origin, t_cylinder *cylinder)
{
	float	*w;
	float	*h;
	float	a;
	float	b;
	float	c;
	float	d;
	float	t;

	h = malloc(sizeof(float) * 3);
	h[0] = cylinder->orient[0];
	h[1] = cylinder->orient[1];
	h[2] = cylinder->orient[2];
	normalize_vector(h);
	w = malloc(sizeof(float) * 3);
	w = vector_two_points(cylinder->coord, origin, w);
	a = 1 - powf(dot_prod(ray, h), 2);
	b = 2 * (dot_prod(ray, w) - dot_prod(ray, h) * dot_prod(w, h));
	c = dot_prod(w, w) - powf(dot_prod(w, h), 2)
		- powf((cylinder->diameter) / 2, 2);
	free(w);
	free(h);
	d = powf(b, 2) - 4 * a * c;
	if (d < 0)
		return (0);
	else
	{
		if (d == 0)
			return (-b / (2 * a));
		else
		{
			t = (-b - sqrtf(d)) / (2 * a);
			if (t < 0)
			{
				t = (-b + sqrtf(d)) / (2 * a);
				if (t < 0)
					return (0);
			}
		}
	}
	return (t);
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
		t = intersection_cylinder(ray, data->camera.coord, current);
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
