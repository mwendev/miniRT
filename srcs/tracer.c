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

float	*calculate_ray_vector(float pixel_size, int *i, t_data *data,
		float *ray_v)
{
	float	ik;
	float	jk;

//	ik = (float)(data->scr_res_h / 2 - i[0]) * pixel_size;
	ik = (float)(HEIGHT / 2 - i[0]) * pixel_size;
//	jk = (float)(data->scr_res_w / 2 - i[1]) * pixel_size;
	jk = (float)(WIDTH / 2 - i[1]) * pixel_size;
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
	if (data->intersection == '0')
	{
		data->intersection = '1';
		data->nearest_point = t;
	}
	else if (data->nearest_point < t)
		data->nearest_point = t;
	data->cross_p[0] = data->camera.coord[0] + ray[0] * t;
	data->cross_p[1] = data->camera.coord[1] + ray[1] * t;
	data->cross_p[2] = data->camera.coord[2] + ray[2] * t;
}

void	intersection_sphere(float *ray, t_data *data)
{
	float	b[3];
	float	t;

	b[0] = 2 * (ray[0] * (data->camera.coord[0] - data->spheres[0].coord[0])
			+ ray[1] * (data->camera.coord[1] - data->spheres[0].coord[1])
			+ ray[2] * (data->camera.coord[2] - data->spheres[0].coord[2]));
	b[1] = powf((data->camera.coord[0] - data->spheres[0].coord[0]), 2)
		+ powf((data->camera.coord[1] - data->spheres[0].coord[1]), 2)
		+ powf((data->camera.coord[2] - data->spheres[0].coord[2]), 2)
		- powf((data->spheres[0].diameter / 2), 2);
	b[2] = powf(b[0], 2) - 4 * b[1];
	if (b[2] < 0)
		return ;
	else
	{
		t = (-b[0] - sqrtf(b[2])) / 2;
		if (t > 0)
			intersection_coords(ray, data, t);
		else
		{
			t = (-b[0] + sqrtf(b[2])) / 2;
			if (t > 0)
				intersection_coords(ray, data, t);
		}
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


int	get_color(t_data *data, int *i, float *ray_v)
{
	intersection_sphere(ray_v, data);
	if (data->intersection == '1')
		data->curr_col = create_trgb((int)(data->ambient.ratio * 255), data->ambient.rgb[0], data->ambient.rgb[1], data->ambient.rgb[2]);
//		data->curr_col = data->ambient.color;
	else
		data->curr_col = 0;
}

void	fill_image(t_data *data)
{
	int		i[2];
	float	pixel_size;
	float	*ray_v;

	i[0] = -1;
	camera_up_right(data);
	pixel_size = (float)(tan(data->camera.fov * PI / 2 / 180)
			/ (float)(WIDTH / 2));
//			/ (float)(data->scr_res_w / 2));
	while (++i[0] < HEIGHT)
//	while (++i[0] < data->scr_res_h)
	{
		i[1] = -1;
		while (++i[1] < WIDTH)
//		while (++i[1] < data->scr_res_w)
		{
			data->intersection = '0';
			ray_v = malloc(sizeof(float) * 3);
			ray_v = calculate_ray_vector(pixel_size, i, data, ray_v);
			normalize_vector(ray_v);
			get_color(data, i, ray_v);
			put_pixel(data, i);
//			if (data->intersection == '1')
//				printf("1");
//			else
//				printf("0");
			free(ray_v);
		}
//		printf("\n");
	}
}
