/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:11:10 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/04 20:11:12 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	while (++i < 2)
	{
		tmp = fabs(90 - angle_axes[i] * 180 / PI);
		if ((min_value + 5) > tmp)
		{
			min_value = tmp;
			res_axis = i;
		}
	}
	return (res_axis);
}

float	*camera_up(t_data *data)
{
	double			*angle_axes;
	static float	vect_axes[3][3] = {
	{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f},
	};
	float			*interm_vect;
	float			*res_vect;

	interm_vect = cross_product(data->camera.orient,
			vect_axes[axis_up(angle_axes, data, vect_axes)]);
	res_vect = cross_product(data->camera.orient, interm_vect);
	free(interm_vect);
	return (res_vect);
}

void	camera_right(t_data *data)
{
}

void	pre_process_camera(t_data *data)
{
	float	*test;

	test = malloc(sizeof(float) * 3);
	test = camera_up(data);
	printf("%f\n", test[0]);
}
