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
	data->cross_p[0] = data->camera.coord[0] + ray[0] * t;
	data->cross_p[1] = data->camera.coord[1] + ray[1] * t;
	data->cross_p[2] = data->camera.coord[2] + ray[2] * t;
}

void	check_nearest_point(t_data *data, float t)
{
	if (data->intersection == '0')
	{
		data->intersection = '1';
		data->nearest_point = t;
	}
	else if (data->nearest_point < t)
		data->nearest_point = t;
}

float	intersection_sphere(float *ray, float *origin, t_sphere *sphere)
{
	float	b[3];
	float	t;

	b[0] = 2 * (ray[0] * (origin[0] - sphere->coord[0])
			+ ray[1] * (origin[1] - sphere->coord[1])
			+ ray[2] * (origin[2] - sphere->coord[2]));
	b[1] = powf((origin[0] - sphere->coord[0]), 2)
		+ powf((origin[1] - sphere->coord[1]), 2)
		+ powf((origin[2] - sphere->coord[2]), 2)
		- powf((sphere->diameter / 2), 2);
	b[2] = powf(b[0], 2) - 4 * b[1];
	if (b[2] < 0)
		return (0);
	else
	{
		t = (-b[0] - sqrtf(b[2])) / 2;
		if (t > 0)
			return t;
//			check_nearest_point(data, t);
		else
		{
			t = (-b[0] + sqrtf(b[2])) / 2;
			if (t > 0)
				return (t);
//				check_nearest_point(data, t);
		}
	}
	return (0);
}

float	*normal_vector_sp(t_data *data, float *intersect)
{
	float	*res;

	res = malloc(sizeof(float) * 3);
	res = vector_two_points(data->spheres->coord, intersect, res);
	normalize_vector(res);
	return (res);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	mix_colors(t_data *data, int *rgb, float tr, float angle)
{
//	data->curr_col_rgb[0] = data->curr_col_rgb[0] + (int)((float)rgb[0] * fabs((double)cosf(angle)) * tr);
//	data->curr_col_rgb[1] = data->curr_col_rgb[1] + (int)((float)rgb[1] * fabs((double)cosf(angle)) * tr);
//	data->curr_col_rgb[2] = data->curr_col_rgb[2] + (int)((float)rgb[2] * fabs((double)cosf(angle)) * tr);
	data->curr_col_rgb[0] = data->curr_col_rgb[0] + (int)((float)rgb[0] * fabs((double)cosf(angle)) * tr);
	data->curr_col_rgb[1] = data->curr_col_rgb[1] + (int)((float)rgb[1] * fabs((double)cosf(angle)) * tr);
	data->curr_col_rgb[2] = data->curr_col_rgb[2] + (int)((float)rgb[2] * fabs((double)cosf(angle)) * tr);
}

void	handle_spheres(float *ray, t_data *data)
{
	float	t;

	t = intersection_sphere(ray, data->camera.coord, data->spheres);
	if (t > 0)
		check_nearest_point(data, t);
	if (data->intersection == '1')
	{
		mix_colors(data, data->ambient.rgb, data->ambient.ratio, 0);
//		data->curr_col = create_trgb(0,
//		data->curr_col = create_trgb((int) (data->ambient.ratio * 255),
//									 (int)((float)data->ambient.rgb[0] * data->ambient.ratio),
//									 (int)((float)data->ambient.rgb[1] * data->ambient.ratio),
//									 (int)((float)data->ambient.rgb[2] * data->ambient.ratio));
//		data->curr_col = data->ambient.color;
//		mlx_pixel_put(data->mlx, data->mlx_win, i[1], i[0], data->curr_col);
	}
}

int	check_light(t_data *data, float *point)
{
	float	t;
	float	*ray;

	ray = malloc(sizeof(float) * 3);
	ray = vector_two_points(point, data->lights->coord, ray);
	normalize_vector(ray);
	t = intersection_sphere(ray, data->cross_p, data->spheres);
	free(ray);
	if (t > 0)
//	if (fabs(t) > 0)
		return (0);
	return (1);
}


int	get_color(t_data *data, float *ray_v, int *i)
{
	float	*norm_sp;
	float	*cross_to_light;

	data->curr_col_rgb[0] = 0;
	data->curr_col_rgb[1] = 0;
	data->curr_col_rgb[2] = 0;
	handle_spheres(ray_v, data);
	intersection_coords(ray_v, data, data->nearest_point - 0.0001);
	if (data->intersection == '1' && check_light(data, data->cross_p))
	{
		cross_to_light = malloc(sizeof (float) * 3);
		cross_to_light = vector_two_points(data->cross_p, data->lights->coord, cross_to_light);
		normalize_vector(cross_to_light);
		norm_sp = normal_vector_sp(data, data->cross_p);
		mix_colors(data, data->lights->rgb, angle_vect(norm_sp, cross_to_light), data->lights->ratio);
		free(cross_to_light);
		free(norm_sp);
	}
//	data->curr_col = create_trgb(0,
//								 (int)((float)data->ambient.rgb[0] * data->ambient.ratio),
//								 (int)((float)data->ambient.rgb[1] * data->ambient.ratio),
//								 (int)((float)data->ambient.rgb[2] * data->ambient.ratio));
	data->curr_col = create_trgb(0,
								 data->curr_col_rgb[0],
								 data->curr_col_rgb[1],
								 data->curr_col_rgb[2]);
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
			get_color(data, ray_v, i);
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
