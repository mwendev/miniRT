/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:02:53 by mwen              #+#    #+#             */
/*   Updated: 2022/04/11 15:29:53 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	listen_mouse_pressed(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	(void)button;
	// if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN
	// 	|| button == LX_MOUSE_SCROLL_UP || button == LX_MOUSE_SCROLL_DOWN)
	// 	printf("need zoom function");
	// else if (button == MOUSE_LEFT_BUTTON || button == LX_MOUSE_LEFT_BUTTON)
	data->mouse->pressed = 1;
	return (0);
}

int	listen_mouse_released(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	(void)button;
	data->mouse->pressed = 0;
	return (0);
}

int	listen_mouse_moved(int x, int y, t_data *data)
{
	data->mouse->prev_x = data->mouse->x;
	data->mouse->prev_y = data->mouse->y;
	data->mouse->x = x;
	data->mouse->y = y;
	// if (data->mouse->pressed == 1)
	// {
		// data->cam->ry += (x - data->mouse->prev_x) * 0.002;
		// data->cam->rx += (y - data->mouse->prev_y) * 0.002;
		// 
	// }
	return (0);
}

void	listen_select(int key, t_data *data)
{
	if (key == MAC_C || key == XK_c)
		select_shape('c', data);
	else if (key == MAC_L || key == XK_l)
		select_shape('l', data);
	else if (key == MAC_S || key == XK_s)
		select_shape('s', data);
	else if (key == MAC_P || key == XK_p)
		select_shape('p', data);
	else if (key == MAC_Y || key == XK_y)
		select_shape('y', data);
	else if (key == MAC_O || key == XK_o)
		select_shape('o', data);
}

int	listen_key(int key, t_data *data)
{
	listen_select(key, data);
	if (key == MAC_EXC || key == XK_Escape)
		terminate(data, NULL, 1);
	else if (key == MAC_1 || key == MAC_2 || key == MAC_3 || key == MAC_Q
		|| key == MAC_W || key == MAC_E || key == XK_1 || key == XK_2
		|| key == XK_3 || key == XK_q || key == XK_w || key == XK_e)
		translate(key, data);
	else if (key == MAC_H || key == XK_h || key == MAC_M || key == XK_m
		|| key == MAC_K || key == XK_k || key == MAC_B || key == XK_b
		|| key == MAC_J || key == XK_j || key == MAC_N || key == XK_n)
		rotate(key, data);
	else if (key == MAC_PLUS || key == XK_plus
		|| key == MAC_MINUS || key == XK_minus)
		resize(key, data);
	return (0);
}
