/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_light_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:08:32 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/27 10:08:33 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

float	*handle_sp_diff(t_data *data)
{
	int			j;
	t_sphere	*current_sp;

	j = -1;
	current_sp = data->spheres;
	while (++j < data->obj_counter.number)
		current_sp = current_sp->next;
	return (normal_vector_sp(current_sp, data->cross_p));
}

float	*handle_pl_diff(t_data *data)
{
	int			j;
	t_plane		*current_pl;
	float		*norm_obj;

	j = -1;
	norm_obj = malloc(sizeof(float) * 3);
	current_pl = data->planes;
	while (++j < data->obj_counter.number)
		current_pl = current_pl->next;
	norm_obj[0] = current_pl->orient[0] * data->plane_norm_koeff;
	norm_obj[1] = current_pl->orient[1] * data->plane_norm_koeff;
	norm_obj[2] = current_pl->orient[2] * data->plane_norm_koeff;
	return (norm_obj);
}

float	*handle_cyl_diff(t_data *data)
{
	int			j;
	t_cylinder	*current_cyl;
	float		*norm_obj;

	j = -1;
	current_cyl = data->cylinders;
	while (++j < data->obj_counter.number)
		current_cyl = current_cyl->next;
	if (data->obj_counter.shape == 'y')
		return (normal_vector_cyl_body(current_cyl, data->cross_p));
	else
	{
		norm_obj = malloc(sizeof(float) * 3);
		norm_obj[0] = current_cyl->orient[0];
		norm_obj[1] = current_cyl->orient[1];
		norm_obj[2] = current_cyl->orient[2];
		return (norm_obj);
	}
}

void	manage_light(t_data *data, t_light *light)
{
	float		*norm_obj;
	float		*cross_to_light;
	float		angle_v;

	if (data->obj_counter.shape == 's')
		norm_obj = handle_sp_diff(data);
	else if (data->obj_counter.shape == 'p')
		norm_obj = handle_pl_diff(data);
	else if (data->obj_counter.shape == 'y' || data->obj_counter.shape == 'z')
		norm_obj = handle_cyl_diff(data);
	cross_to_light = malloc(sizeof(float) * 3);
	cross_to_light = vector_two_points(data->cross_p, light->coord,
			cross_to_light);
	normalize_vector(cross_to_light);
	angle_v = angle_vect(norm_obj, cross_to_light);
	mix_light(data, light->rgb, angle_v, light->ratio);
	free(cross_to_light);
	free(norm_obj);
}

int	diffuse_light(t_data *data)
{
	t_light		*light;

	light = data->lights;
	while (light != NULL)
	{
		if (data->intersection == '1'
			&& check_diffuse_light(data, data->cross_p, light))
			manage_light(data, light);
		light = light->next;
	}
	data->curr_col = create_trgb(0, data->curr_col_rgb[0],
			data->curr_col_rgb[1], data->curr_col_rgb[2]);
	return (data->curr_col);
}
