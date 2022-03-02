/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:43:49 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/01 15:43:52 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	angle_vect(float *vect1, float *vect2)
{
	double	dot_prod;
	double	mod_vect1;
	double	mod_vect2;

	dot_prod = vect1[0] * vect2[0] + vect1[1] * vect2[1] + vect1[2] * vect2[2];
	mod_vect1 = sqrt(pow(vect1[0], 2) + pow(vect1[1], 2) + pow(vect1[2], 2));
	mod_vect2 = sqrt(pow(vect2[0], 2) + pow(vect2[1], 2) + pow(vect2[2], 2));
	return (acos(dot_prod/(mod_vect1 * mod_vect2)));
}

float	*camera_up(t_data *data)
{
	double	angle_nx;
	double	angle_ny;
	double	angle_nz;

	angle_nx = angle_vect(data->camera.orient, (float[3]){1.0f,0.0f,0.0f});
	angle_ny = angle_vect(data->camera.orient, (float[3]){0.0f,1.0f,0.0f});
	angle_nz = angle_vect(data->camera.orient, (float[3]){0.0f,0.0f,1.0f});
}

void	camera_right(t_data *data)
{}