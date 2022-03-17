/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:49:36 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/16 20:34:44 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_data(t_data *data)
{
	data->img = NULL;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->ambient.ratio = 0;
	data->ambient.color = 16777215;
	data->camera.coord[0] = 0;
	data->camera.coord[1] = 0;
	data->camera.coord[2] = 0;
	data->camera.orient[0] = 0;
	data->camera.orient[1] = 0;
	data->camera.orient[2] = 0;
	data->camera.fov = 0;
	data->mouse = malloc(sizeof(t_mouse));
	data->lights = NULL;
	data->planes = NULL;
	data->spheres = NULL;
	data->cylinders = NULL;
}

void	set_listener(t_data *data)
{
	mlx_key_hook(data->mlx_win, listen_key, data);
	mlx_hook(data->mlx_win, 2, 0, listen_key, data);
	mlx_hook(data->mlx_win, 4, 1L<<2, listen_mouse_pressed, data);
	mlx_hook(data->mlx_win, 5, 1L<<3, listen_mouse_released, data);
	mlx_hook(data->mlx_win, 6, 0, listen_mouse_moved, data);
	mlx_hook(data->mlx_win, 17, 0, shut_down, data);
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		terminate(data, "Init mlx failed", 1);
	data->mlx_win = mlx_new_window(data->mlx, WIDTH + 200, HEIGHT, "miniRT");
	if (!data->mlx_win)
		terminate(data, "Init window failed", 1);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		terminate(data, "Init image failed", 1);
	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
		&data->line_len, &data->endian);
//	mlx_loop(data->mlx);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		terminate(NULL, "Invalid input", 1);
	init_data(&data);
	parse(argv[1], &data);
//	data.scr_res_h = HEIGHT;
//	data.scr_res_w = WIDTH;
	init_window(&data);
	fill_image(&data);
	set_listener(&data);
	mlx_loop(data.mlx);
}
