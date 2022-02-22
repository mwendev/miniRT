/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:14:01 by mwen              #+#    #+#             */
/*   Updated: 2021/11/21 16:43:30 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	init_camera(t_fdf *data)
{
	int	menu_wid;

	menu_wid = WIDTH / 4;
	if (!data->map->wid)
		data->map->wid = 1;
	if (!data->map->hgt)
		data->map->hgt = 1;
	if ((WIDTH - menu_wid) / data->map->wid / 2 < HEIGHT / data->map->hgt / 2)
		data->cam->zoom = (WIDTH - menu_wid) / data->map->wid / 2;
	else
		data->cam->zoom = HEIGHT / data->map->hgt / 2;
	data->cam->projection = 1;
	data->cam->move_x = 0;
	data->cam->move_y = 0;
	data->cam->move_z = 1;
	data->cam->rx = 0;
	data->cam->ry = 0;
	data->cam->rz = 0;
}

void	init_image(t_fdf *data)
{
	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_len, &data->endian);
}

void	init_data(t_fdf *data, char *file_name)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		terminate(ERR_INIT_MAP, data);
	read_map(data, file_name);
	data->cam = malloc(sizeof(t_cam));
	if (!data->cam)
		terminate(ERR_INIT_CAM, data);
	init_camera(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		terminate(ERR_INIT_MLX, data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "FDF");
	if (!data->win)
		terminate(ERR_INIT_WINDOW, data);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		terminate(ERR_INIT_IMG, data);
	init_image(data);
	data->mouse = malloc(sizeof(t_mouse));
	if (!data->mouse)
		terminate(ERR_INIT_MOUSE, data);
}
