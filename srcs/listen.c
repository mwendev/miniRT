/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:02:53 by mwen              #+#    #+#             */
/*   Updated: 2022/03/16 13:10:51 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	listen_mouse_pressed(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN
		|| button == LX_MOUSE_SCROLL_UP || button == LX_MOUSE_SCROLL_DOWN)
		printf("need zoom function");
	else if (button == MOUSE_LEFT_BUTTON || button == LX_MOUSE_LEFT_BUTTON)
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
	if (data->mouse->pressed == 1)
	{
		printf("mouse pressed change camera and draw\n");
	}
	return (0);
}

int	listen_key(int key, t_data *data)
{
	if (key == MAC_EXC || key == XK_Escape)
		terminate(data, NULL, 1);
	else if (key == MAC_C || key == XK_C)
		select('c', data);
	else if (key == MAC_L || key == XK_L)
		select('l', data);
	else if (key == MAC_S || key == XK_S)
		select('s', data);
	else if (key == MAC_P || key == XK_P)
		select('p', data);
	else if (key == MAC_Y || key == XK_Y)
		select('y', data);
	else if (key == MAC_O || key == XK_O)
		select('o', data);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP
		|| key == ARROW_DOWN || key == LX_ARROW_LEFT || key == LX_ARROW_RIGHT
		|| key == LX_ARROW_UP || key == LX_ARROW_DOWN)
		printf("need translation function\n");
	else if (key == MAIN_PAD_Z || key == MAIN_PAD_X || key == LX_MAIN_PAD_Z
		|| key == LX_MAIN_PAD_X)
		printf("do we need these keys?\n");
	else if (key == MAIN_PAD_PLUS || key == MAIN_PAD_MINUS
		|| key == LX_MAIN_PAD_PLUS || key == LX_MAIN_PAD_MINUS)
		printf("do we need to zoom?\n");
	else if (key == MAIN_PAD_I || key == MAIN_PAD_P || key == LX_MAIN_PAD_I
		|| key == LX_MAIN_PAD_P)
		printf("what can we do with I and P?\n");
	return (0);
}

int	shut_down(t_data *data)
{
	terminate(data, NULL, 1);
	return (0);
}