/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:11:10 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/14 17:25:22 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* z - 0
 * x - 1
 * y - 2 */

int	axis_up(double *angle_axes, t_data *data, float vect_axes[3][3])
{
	int				res_axis;
	double			min_value;
	double			tmp;
	int				i;

	res_axis = 0;
	angle_axes[0] = angle_vect(data->camera.orient, vect_axes[0]);
	angle_axes[1] = angle_vect(data->camera.orient, vect_axes[1]);
	angle_axes[2] = angle_vect(data->camera.orient, vect_axes[2]);
	i = 0;
	min_value = fabs(90 - angle_axes[0] * 180 / PI);
	while (++i <= 2)
	{
		tmp = fabs(90 - angle_axes[i] * 180 / PI);
		if (min_value > tmp + 1)
		{
			min_value = tmp;
			res_axis = i;
		}
	}
	return (res_axis);
}

void	camera_up_right(t_data *data)
{
	double			*angle_axes;
	static float	vect_axes[3][3] = {
	{0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
	};
	float			*interm_vect;

	normalize_vector(data->camera.orient);
	interm_vect = malloc(sizeof(float) * 3);
	angle_axes = malloc(sizeof(double) * 3);
	cross_product(data->camera.orient,
			vect_axes[axis_up(angle_axes, data, vect_axes)], interm_vect);
	cross_product(interm_vect, data->camera.orient, data->camera.up);
	free(interm_vect);
	cross_product(data->camera.orient, data->camera.up, data->camera.right);
	normalize_vector(data->camera.up);
	normalize_vector(data->camera.right);
}
