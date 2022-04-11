/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:10:16 by mwen              #+#    #+#             */
/*   Updated: 2022/04/11 15:23:06 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	operate_z(float *x, float *y, float *z, t_data *data)
{
	if (data->selected.shape == 'c')
	{
		x = &data->camera.orient[0];
		y = &data->camera.orient[1];
		z = &data->camera.orient[2];
	}
	else if (data->selected.shape == 'y')
	{
		x = &data->cylinders->orient[0];
		y = &data->cylinders->orient[1];
		z = &data->cylinders->orient[2];
	}
	else if (data->selected.shape == 'p')
	{
		x = &data->planes->orient[0];
		y = &data->planes->orient[1];
		z = &data->planes->orient[2];
	}
	*x = *x * cos(data->rotation[2]) - *y * sin(data->rotation[2]);
	*y = *x * sin(data->rotation[2]) * -1 + *y * cos(data->rotation[2]);
}

void	operate_y(float *x, float *y, float *z, t_data *data)
{
	if (data->selected.shape == 'c')
	{
		x = &data->camera.orient[0];
		y = &data->camera.orient[1];
		z = &data->camera.orient[2];
	}
	else if (data->selected.shape == 'y')
	{
		x = &data->cylinders->orient[0];
		y = &data->cylinders->orient[1];
		z = &data->cylinders->orient[2];
	}
	else if (data->selected.shape == 'p')
	{
		x = &data->planes->orient[0];
		y = &data->planes->orient[1];
		z = &data->planes->orient[2];
	}
	*x = *x * cos(data->rotation[1]) + *z * cos(data->rotation[1]) * -1;
	*z = *x * sin(data->rotation[1]) + *z * cos(data->rotation[1]);
}

void	operate_x(float *x, float *y, float *z, t_data *data)
{
	if (data->selected.shape == 'c')
	{
		x = &data->camera.orient[0];
		y = &data->camera.orient[1];
		z = &data->camera.orient[2];
	}
	else if (data->selected.shape == 'y')
	{
		x = &data->cylinders->orient[0];
		y = &data->cylinders->orient[1];
		z = &data->cylinders->orient[2];
	}
	else if (data->selected.shape == 'p')
	{
		x = &data->planes->orient[0];
		y = &data->planes->orient[1];
		z = &data->planes->orient[2];
	}
	*y = *y * cos(data->rotation[0]) + *z * sin(data->rotation[0]);
	*z = *y * sin(data->rotation[0]) * -1 + *z * cos(data->rotation[0]);
}

void	set_rotation(int key, t_data *data)
{
	float	prev[3];
	int		i;

	prev[0] = data->rotation[0];
	prev[1] = data->rotation[1];
	prev[2] = data->rotation[2];
	if (key == MAC_H || key == XK_h)
		data->rotation[0] -= 0.5;
	else if (key == MAC_M || key == XK_m)
		data->rotation[0] += 0.5;
	else if (key == MAC_K || key == XK_k)
		data->rotation[1] += 0.5;
	else if (key == MAC_B || key == XK_b)
		data->rotation[1] -= 0.5;
	else if (key == MAC_J || key == XK_j)
		data->rotation[2] += 0.5;
	else if (key == MAC_N || key == XK_n)
		data->rotation[2] -= 0.5;
	i = -1;
	while (++i >= 0 && i < 3)
		if (data->rotation[i] == 0 && prev[i])
			data->rotation[i] = prev[i] * -1;
}

void	rotate(int key, t_data *data)
{
	if (distribute(data))
		return ;
	set_rotation(key, data);
	if (key == MAC_H || key == XK_h || key == MAC_M || key == XK_m)
		operate_x(0, 0, 0, data);
	else if (key == MAC_K || key == XK_k || key == MAC_B || key == XK_b)
		operate_y(0, 0, 0, data);
	else if (key == MAC_J || key == XK_j || key == MAC_N || key == XK_n)
		operate_z(0, 0, 0, data);
	rewind_link(data);
	fill_image(data);
}
