/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_licht_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:08:28 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/27 10:08:30 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	check_sp_diff(t_data *data, float t, float *ray)
{
	t_sphere	*current_sp;

	current_sp = data->spheres;
	while (current_sp != NULL)
	{
		t = intersection_sphere(ray, data->cross_p, current_sp);
		if (t > 0)
		{
			if (t > data->nearest_point)
				t = 0;
			else
				break ;
		}
		current_sp = current_sp->next;
	}
	return (t);
}

float	check_pl_diff(t_data *data, float t, float *ray, float *point)
{
	t_plane		*current_pl;
	float		*a;
	float		v0;

	a = malloc(sizeof(float) * 4);
	current_pl = data->planes;
	while (current_pl != NULL)
	{
		a = normalize_plane(current_pl->orient, current_pl->coord, a);
		v0 = -(a[0] * point[0] + a[1] * point[1]
				+ a[2] * point[2] + a[3]);
		t = intersection_plane(ray, a, v0);
//		t = intersection_plane(data, ray, a, v0);
		if (t > 0)
		{
			if (t > data->nearest_point)
				t = 0;
			else
				break ;
		}
		current_pl = current_pl->next;
	}
	free(a);
	return (t);
}

float	check_cyl_diff(t_data *data, float t, float *ray)
{
	t_cylinder	*current_cyl;

	current_cyl = data->cylinders;
	while (current_cyl != NULL)
	{
		t = intersection_cylinder_body(ray, data->cross_p, current_cyl);
		if (t > 0)
		{
			if (t < data->nearest_point)
//			if (t > data->nearest_point)
//				t = 0;
//			else
				break ;
		}
		t = intersection_cylinder_cap(ray, data->cross_p, current_cyl, 0);
		if (t > 0)
		{
			if (t > data->nearest_point)
				t = 0;
			else
				break ;
		}
		t = intersection_cylinder_cap(ray, data->cross_p, current_cyl, 1);
		if (t > 0)
		{
			if (t > data->nearest_point)
				t = 0;
			else
				break ;
		}
		current_cyl = current_cyl->next;
	}
	return (t);
}

int	check_diffuse_light(t_data *data, float *point)
{
	float		t;
	float		*ray;

	ray = malloc(sizeof(float) * 3);
	ray = vector_two_points(point, data->lights->coord, ray);
	normalize_vector(ray);
	t = check_sp_diff(data, t, ray);
	if (t == 0)
		t = check_pl_diff(data, t, ray, point);
	if (t == 0)
		t = check_cyl_diff(data, t, ray);
	free(ray);
	if (t > 0)
		return (0);
	return (1);
}
