/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:10:16 by mwen              #+#    #+#             */
/*   Updated: 2022/04/11 20:07:08 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	operate_z(float *x, float *y, t_data *data)
{
	if (!x || !y)
		return ;
	*x = *x * cos(data->rotation[2]) - *y * sin(data->rotation[2]);
	*y = *x * sin(data->rotation[2]) + *y * cos(data->rotation[2]);
}

void	operate_y(float *x, float *z, t_data *data)
{
	if (!x || !z)
		return ;
	*x = *x * cos(data->rotation[1]) + *z * sin(data->rotation[1]);
	*z = *x * sin(data->rotation[1]) * -1 + *z * cos(data->rotation[1]);
}

void	operate_x(float *y, float *z, t_data *data)
{
	if (!y || !z)
		return ;
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
		data->rotation[0] -= 0.25;
	else if (key == MAC_M || key == XK_m)
		data->rotation[0] += 0.25;
	else if (key == MAC_K || key == XK_k)
		data->rotation[1] += 0.25;
	else if (key == MAC_B || key == XK_b)
		data->rotation[1] -= 0.25;
	else if (key == MAC_J || key == XK_j)
		data->rotation[2] += 0.25;
	else if (key == MAC_N || key == XK_n)
		data->rotation[2] -= 0.25;
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
		operate_x(select_orient(1, data), select_orient(2, data), data);
	else if (key == MAC_K || key == XK_k || key == MAC_B || key == XK_b)
		operate_y(select_orient(0, data), select_orient(2, data), data);
	else if (key == MAC_J || key == XK_j || key == MAC_N || key == XK_n)
		operate_z(select_orient(0, data), select_orient(1, data), data);
	rewind_link(data);
	fill_image(data);
}
