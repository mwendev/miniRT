/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:44:03 by mwen              #+#    #+#             */
/*   Updated: 2021/11/22 11:54:34 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	rotate(int key, t_fdf *data)
{
	if (key == MAIN_PAD_W || key == LX_MAIN_PAD_W)
		data->cam->rx += 0.5;
	else if (key == MAIN_PAD_S || key == LX_MAIN_PAD_S)
		data->cam->rx -= 0.5;
	else if (key == MAIN_PAD_D || key == LX_MAIN_PAD_D)
		data->cam->ry -= 0.5;
	else if (key == MAIN_PAD_A || key == LX_MAIN_PAD_A)
		data->cam->ry += 0.5;
	else if (key == MAIN_PAD_E || key == LX_MAIN_PAD_E)
		data->cam->rz += 0.5;
	else if (key == MAIN_PAD_Q || key == LX_MAIN_PAD_Q)
		data->cam->rz -= 0.5;
	draw(data);
}

void	move(int key, t_fdf *data)
{
	if (key == ARROW_LEFT || key == LX_ARROW_LEFT)
		data->cam->move_x -= 10;
	else if (key == ARROW_RIGHT || key == LX_ARROW_RIGHT)
		data->cam->move_x += 10;
	else if (key == ARROW_UP || key == LX_ARROW_UP)
		data->cam->move_y -= 10;
	else
		data->cam->move_y += 10;
	draw(data);
}

void	flatten(int key, t_fdf *data)
{
	if (key == MAIN_PAD_Z || key == LX_MAIN_PAD_Z)
		data->cam->move_z -= 0.1;
	else if (key == MAIN_PAD_X || key == LX_MAIN_PAD_X)
		data->cam->move_z += 0.1;
	if (data->cam->move_z < 0.1)
		data->cam->move_z = 0.1;
	else if (data->cam->move_z > 10)
		data->cam->move_z = 10;
	draw(data);
}

void	zoom(int key, t_fdf *data)
{
	if (key == MAIN_PAD_PLUS || key == MOUSE_SCROLL_UP
		|| key == LX_MAIN_PAD_PLUS || key == LX_MOUSE_SCROLL_UP)
		data->cam->zoom++;
	else if (key == MAIN_PAD_MINUS || key == MOUSE_SCROLL_DOWN
		|| key == LX_MAIN_PAD_MINUS || key == LX_MOUSE_SCROLL_DOWN)
		data->cam->zoom--;
	if (data->cam->zoom < 1)
		data->cam->zoom = 1;
	draw(data);
}

void	change_projection(int key, t_fdf *data)
{
	data->cam->rx = 0;
	data->cam->ry = 0;
	data->cam->rz = 0;
	if (key == MAIN_PAD_I || key == LX_MAIN_PAD_I)
		data->cam->projection = 1;
	else
		data->cam->projection = 0;
	draw(data);
}
