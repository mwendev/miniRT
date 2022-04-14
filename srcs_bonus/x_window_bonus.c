/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_window.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:51:22 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/04/14 15:02:04 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	terminate1(t_data *data)
{
	if (data)
	{
		if (data->mlx && data->mlx_win)
		{
			mlx_destroy_image(data->mlx, data->img);
			mlx_destroy_window(data->mlx, data->mlx_win);
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
		if (data->mouse)
			free(data->mouse);
		free_light(data);
		free_spheres(data);
		free_plane(data);
		free_cylinder(data);
	}
	exit (0);
}

int	redraw(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 200, 0);
	put_menu(data);
	return (0);
}
