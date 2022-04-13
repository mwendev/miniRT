/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:28:26 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/30 10:28:44 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	cap_center(t_cylinder *cylinder, float *center, float offset)
{
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
	cap_center(cylinder, center, offset);
	a = malloc(sizeof(float) * 4);
	a = normalize_plane(cylinder->orient, center, a);
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
