/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:04:55 by mwen              #+#    #+#             */
/*   Updated: 2022/03/16 20:00:44 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_shape(char shape, t_data *data)
{
	void	*img;

	if (data->selected.shape == shape && shape != 'c')
		data->selected.number++;
	else
		data->selected.number = 0;
	img = mlx_new_image(data->mlx, 200, HEIGHT);
	mlx_put_image_to_window(data->mlx, data->mlx_win, img, 0, 0);
	data->selected.shape = shape;
	mlx_destroy_image(data->mlx, img);
	put_menu(data);
}
