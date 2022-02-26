/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:49:36 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/02/26 16:06:00 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	init(t_data *data)
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
	data->lights = NULL;
	data->planes = NULL;
	data->spheres = NULL;
	data->cylinders = NULL;
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		terminate(NULL, "Invalid input", 1);
	init(&data);
	parse(argv[1], &data);
	terminate(&data, NULL, 0);
}
