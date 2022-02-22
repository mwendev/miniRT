/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:09:21 by mwen              #+#    #+#             */
/*   Updated: 2021/11/23 18:22:45 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_data(t_fdf *data)
{
	data->cam = NULL;
	data->img = NULL;
	data->map = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->mouse = NULL;
}

int	shut_down(t_fdf *data)
{
	terminate(NULL, data);
	return (0);
}

void	set_listener(t_fdf *data)
{
	mlx_hook(data->win, 2, 0, listen_key, data);
	mlx_hook(data->win, 4, 1L<<2, listen_mouse_pressed, data);
	mlx_hook(data->win, 5, 1L<<3, listen_mouse_released, data);
	mlx_hook(data->win, 6, 0, listen_mouse_moved, data);
	mlx_hook(data->win, 17, 0, shut_down, data);
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc != 2)
		terminate(ERR_USAGE, NULL);
	data = malloc(sizeof(t_fdf));
	if (!data)
		terminate(ERR_INIT_DATA, NULL);
	set_data(data);
	init_data(data, argv[1]);
	draw(data);
	set_listener(data);
	mlx_loop(data->mlx);
}
