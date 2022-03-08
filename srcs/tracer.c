/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:06:46 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/02/25 17:06:46 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/* x - 0
 * y - 1
 * z - 2 */

float	*calculate_ray_vector(float pixel_size, int i, int j, t_data *data, float *ray_v)
{
	float	ik;
	float	jk;

	ik = (float)(data->scr_res_h / 2 - i) * pixel_size;
	jk = (float)(data->scr_res_w / 2 - j) * pixel_size;
	ray_v[0] = data->camera.orient[0] + data->camera.up[0] * ik +
			data->camera.right[0] * jk;
	ray_v[1] = data->camera.orient[1] + data->camera.up[1] * ik +
			data->camera.right[1] * jk;
	ray_v[2] = data->camera.orient[2] + data->camera.up[2] * ik +
			data->camera.right[2] * jk;
	return (ray_v);
}

void	fill_image(t_data *data)
{
	int		i;
	int		j;
	float	pixel_size;
	float	*ray_v;

	i = -1;
	normalize_vector(data->camera.orient);
	camera_up_right(data);
	normalize_vector(data->camera.up);
	normalize_vector(data->camera.right);
	pixel_size = (float)(tan(data->camera.fov * PI / 2 / 180)
			/ (float)(data->scr_res_w / 2));
	while (++i < data->scr_res_h)
	{
		j = -1;
		while (++j < data->scr_res_w)
		{
			ray_v = malloc(sizeof(float) * 3);
			ray_v = calculate_ray_vector(pixel_size, i, j, data, ray_v);
			free(ray_v);
		}
	}
}
