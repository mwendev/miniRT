/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 22:08:40 by mwen              #+#    #+#             */
/*   Updated: 2021/11/21 23:30:11 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	listen_mouse_pressed(int button, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN
		|| button == LX_MOUSE_SCROLL_UP || button == LX_MOUSE_SCROLL_DOWN)
		zoom(button, data);
	else if (button == MOUSE_LEFT_BUTTON || button == LX_MOUSE_LEFT_BUTTON)
		data->mouse->pressed = 1;
	return (0);
}

int	listen_mouse_released(int button, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	(void)button;
	data->mouse->pressed = 0;
	return (0);
}

int	listen_mouse_moved(int x, int y, t_fdf *data)
{
	data->mouse->prev_x = data->mouse->x;
	data->mouse->prev_y = data->mouse->y;
	data->mouse->x = x;
	data->mouse->y = y;
	if (data->mouse->pressed == 1)
	{
		data->cam->ry += (x - data->mouse->prev_x) * 0.002;
		data->cam->rx += (y - data->mouse->prev_y) * 0.002;
		draw(data);
	}
	return (0);
}

int	listen_key(int key, t_fdf *data)
{
	if (key == MAIN_PAD_ESC || key == LX_MAIN_PAD_ESC)
		terminate(NULL, data);
	if (key == MAIN_PAD_D || key == MAIN_PAD_A || key == MAIN_PAD_W
		|| key == MAIN_PAD_S || key == MAIN_PAD_E || key == MAIN_PAD_Q
		|| key == LX_MAIN_PAD_D || key == LX_MAIN_PAD_A || key == LX_MAIN_PAD_W
		|| key == LX_MAIN_PAD_S || key == LX_MAIN_PAD_E || key == LX_MAIN_PAD_Q)
		rotate(key, data);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP
		|| key == ARROW_DOWN || key == LX_ARROW_LEFT || key == LX_ARROW_RIGHT
		|| key == LX_ARROW_UP || key == LX_ARROW_DOWN)
		move(key, data);
	else if (key == MAIN_PAD_Z || key == MAIN_PAD_X || key == LX_MAIN_PAD_Z
		|| key == LX_MAIN_PAD_X)
		flatten(key, data);
	else if (key == MAIN_PAD_PLUS || key == MAIN_PAD_MINUS
		|| key == LX_MAIN_PAD_PLUS || key == LX_MAIN_PAD_MINUS)
		zoom(key, data);
	else if (key == MAIN_PAD_I || key == MAIN_PAD_P || key == LX_MAIN_PAD_I
		|| key == LX_MAIN_PAD_P)
		change_projection(key, data);
	return (0);
}
