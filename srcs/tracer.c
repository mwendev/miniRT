/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:06:46 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/17 22:02:09 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* x - 0
 * y - 1
 * z - 2 */

float	*calculate_ray_vector(float pixel_size, int *i, t_data *data,
		float *ray_v)
{
	float	ik;
	float	jk;

	ik = ((float)HEIGHT / 2 - (float)i[0]) * pixel_size;
	jk = ((float)WIDTH / 2 - (float)i[1]) * pixel_size;
	ray_v[0] = data->camera.orient[0] + data->camera.up[0] * ik
		+ data->camera.right[0] * jk;
	ray_v[1] = data->camera.orient[1] + data->camera.up[1] * ik
		+ data->camera.right[1] * jk;
	ray_v[2] = data->camera.orient[2] + data->camera.up[2] * ik
		+ data->camera.right[2] * jk;
	return (ray_v);
}

void	intersection_coords(float *ray, t_data *data, float t)
{
	data->cross_p[0] = data->camera.coord[0] + ray[0] * t;
	data->cross_p[1] = data->camera.coord[1] + ray[1] * t;
	data->cross_p[2] = data->camera.coord[2] + ray[2] * t;
}

int	check_nearest_point(t_data *data, float t, int i)
{
	if (data->intersection == '0')
	{
		data->intersection = '1';
		data->nearest_point = t;
		data->obj_counter.number = i;
		return (1);
	}
	else if (data->nearest_point > t)
	{
		data->nearest_point = t;
		data->obj_counter.number = i;
		return (1);
	}
	return (0);
}

void	find_intersection(float *ray_v, t_data *data)
{
	handle_spheres(ray_v, data);
	handle_planes(ray_v, data);
	handle_cylinders(ray_v, data);
}

void	fill_image(t_data *data)
{
	int		i[2];
	float	pixel_size;
	float	*ray_v;

	i[0] = -1;
	camera_up_right(data);
	pixel_size = (float)(tan(data->camera.fov * M_PI / 2 / 180)
			/ (float)(WIDTH / 2));
	while (++i[0] < HEIGHT)
	{
		i[1] = -1;
		while (++i[1] < WIDTH)
		{
			data->curr_col_rgb[0] = 0;
			data->curr_col_rgb[1] = 0;
			data->curr_col_rgb[2] = 0;
			data->intersection = '0';
			ray_v = malloc(sizeof(float) * 3);
			ray_v = calculate_ray_vector(pixel_size, i, data, ray_v);
			normalize_vector(ray_v);
			find_intersection(ray_v, data);
			intersection_coords(ray_v, data, data->nearest_point - 0.0002);
			diffuse_light(data);
			put_pixel(data, i);
			free(ray_v);
		}
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 200, 0);
}
