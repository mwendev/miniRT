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

float	*normal_vector_sp(t_sphere *current, float *intersect)
{
	float	*res;

	res = malloc(sizeof(float) * 3);
	res = vector_two_points(current->coord, intersect, res);
	normalize_vector(res);
	return (res);
}

int	check_light(t_data *data, float *point)
{
	float		t;
	float		*ray;
	t_sphere	*current_sp;
	t_plane		*current_pl;
	float		*a;
	float		v0;

	a = malloc(sizeof(float) * 4);
	ray = malloc(sizeof(float) * 3);
	ray = vector_two_points(point, data->lights->coord, ray);
	normalize_vector(ray);
//	if (data->obj_counter.shape == 's')
//	{
	current_sp = data->spheres;
	while (current_sp != NULL)
	{
		t = intersection_sphere(ray, data->cross_p, current_sp);
		if (t > 0)
			break;
		current_sp = current_sp->next;
	}
//	}
//	else if (data->obj_counter.shape == 'p')
//	{
	if (t < 0.000001)
	{
		current_pl = data->planes;
		while (current_pl != NULL)
		{
			a = normalize_plane(current_pl, a);
			v0 = -(a[0] * point[0] + a[1] * point[1] +
				   a[2] * point[2] + a[3]);
			t = intersection_plane(data, ray, a, v0);
			if (t > 0)
			{
				if (t > data->nearest_point)
					t = 0;
				else
					break ;
			}
			current_pl = current_pl->next;
		}
	}
//	}
	free(a);
	free(ray);
	if (t > 0)
		return (0);
	return (1);
}

void	find_intersection(float *ray_v, t_data *data)
{
	handle_spheres(ray_v, data);
	handle_planes(ray_v, data);
}

int	get_color(t_data *data, float *ray_v, int *i)
{
	float		*norm_obj;
	float		*cross_to_light;
	t_sphere	*current_sp;
	t_plane		*current_pl;
	int			j;

	data->curr_col_rgb[0] = 0;
	data->curr_col_rgb[1] = 0;
	data->curr_col_rgb[2] = 0;
	find_intersection(ray_v, data);
	intersection_coords(ray_v, data, data->nearest_point - 0.0002);
	if (data->intersection == '1' && check_light(data, data->cross_p))
	{
		j = -1;
		if (data->obj_counter.shape == 's')
		{
			current_sp = data->spheres;
			while (++j < data->obj_counter.number)
				current_sp = current_sp->next;
			norm_obj = normal_vector_sp(current_sp, data->cross_p);
		}
		else if (data->obj_counter.shape == 'p')
		{
			norm_obj = malloc(sizeof(float) * 3);
			current_pl = data->planes;
			while (++j < data->obj_counter.number)
				current_pl = current_pl->next;
			norm_obj[0] = current_pl->orient[0] * data->plane_norm_koeff;
			norm_obj[1] = current_pl->orient[1] * data->plane_norm_koeff;
			norm_obj[2] = current_pl->orient[2] * data->plane_norm_koeff;
		}
		cross_to_light = malloc(sizeof (float) * 3);
		cross_to_light = vector_two_points(data->cross_p, data->lights->coord, cross_to_light);
		normalize_vector(cross_to_light);
		mix_light(data, data->lights->rgb, angle_vect(norm_obj, cross_to_light), data->lights->ratio);
		free(cross_to_light);
		free(norm_obj);
	}
	data->curr_col = create_trgb(
			0, data->curr_col_rgb[0], data->curr_col_rgb[1], data->curr_col_rgb[2]);
	return (data->curr_col);
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
			data->intersection = '0';
			ray_v = malloc(sizeof(float) * 3);
			ray_v = calculate_ray_vector(pixel_size, i, data, ray_v);
			normalize_vector(ray_v);
			get_color(data, ray_v, i);
			put_pixel(data, i);
			free(ray_v);
		}
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 200, 0);
}
