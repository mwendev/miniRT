/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:49:36 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/04/12 16:33:58 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_data(t_data *data)
{
	data->img = NULL;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->ambient.ratio = 0;
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
	data->selected.shape = 0;
	data->selected.number = 0;
}

void	check_file(char *argv)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		terminate(NULL, "Invalid input", 1);
	}
	close(fd);
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
	put_menu(data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		check;

	check = 0;
	if (argc != 2)
		terminate(NULL, "Invalid input", 1);
	check_file(argv[1]);
	init_data(&data);
	if (parse(&check, argv[1], &data) || check < 3)
		terminate(&data,
			"Input must contain Ambient lighting AND Camera AND Light", 1);
	data.pixel_size = (float)(tan(data.camera.fov * M_PI / 2 / 180)
			/ (float)(WIDTH / 2));
	init_window(&data);
	fill_image(&data);
	mlx_key_hook(data.mlx_win, listen_key, &data);
	mlx_loop(data.mlx);
}
