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
{}

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
				data->obj_counter.shape = 's';
				mix_ambient(data, data->ambient.rgb, current->rgb,
							data->ambient.ratio);
			}
		}
		current = current->next;
		i++;
	}
}
