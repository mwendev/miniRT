/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:10:16 by mwen              #+#    #+#             */
/*   Updated: 2022/04/10 19:39:33 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	operate_z(t_data *data)
{
	float	*x;
	float	*y;
	float	*z;

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
	// else if (data->selected.shape == 'o')

	*x = *x * cos(data->rotation) - *y * sin(data->rotation);
	*y = *x * sin(data->rotation) * -1 + *y * cos(data->rotation);
}

void	operate_y(t_data *data)
{
	float	*x;
	float	*y;
	float	*z;

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
	// else if (data->selected.shape == 'o')

	*x = *x * cos(data->rotation) + *z * cos(data->rotation) * -1;
	*z = *x * sin(data->rotation) + *z * cos(data->rotation);
}

void	operate_x(t_data *data)
{
	float	*x;
	float	*y;
	float	*z;

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
	// else if (data->selected.shape == 'o')

	*y = *y * cos(data->rotation) + *z * sin(data->rotation);
	*z = *y * sin(data->rotation) * -1 + *z * cos(data->rotation);
}

void	set_rotation(int key, t_data *data)
{
	if (data->selected.shape == 'y' && )
		data->cylinders->coord[axis]++;
	else if (data->selected.shape == 'p')
		data->planes->coord[axis]++;
	else if (data->selected.shape == 'c')
		data->camera.coord[axis]++;
}

void	rotate(int key, t_data *data)
{
	distribute(data);
	set_rotation(key, data);
	if (key == MAC_H || key == XK_h || key == MAC_M || key == XK_m)
		operate_x(data);
	else if (key == MAC_K || key == XK_k || key == MAC_B || key == XK_b)
		operate_y(data);
	else if (key == MAC_J || key == XK_j || key == MAC_N || key == XK_n)
		operate_z(data);
	rewind_link(data);
	fill_image(data);
}
