/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:04:55 by mwen              #+#    #+#             */
/*   Updated: 2022/04/11 15:20:02 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	select_number(int selected, t_data *data)
{
	int	i;
	int	ret;

	i = selected;
	ret = 0;
	if (data->selected.shape == 'l')
		while (i-- && data->lights->next && ++ret)
			data->lights = data->lights->next;
	else if (data->selected.shape == 's')
		while (i-- && data->spheres->next && ++ret)
			data->spheres = data->spheres->next;
	else if (data->selected.shape == 'y')
		while (i-- && data->cylinders->next && ++ret)
			data->cylinders = data->cylinders->next;
	else if (data->selected.shape == 'p')
		while (i-- && data->planes->next && ++ret)
			data->planes = data->planes->next;
	rewind_link(data);
	if (selected - ret)
		return (0);
	return (ret);
}

void	select_shape(char shape, t_data *data)
{
	void	*img;

	data->rotation[0] = 0;
	data->rotation[1] = 0;
	data->rotation[2] = 0;
	if (data->selected.shape == shape && shape != 'c')
		data->selected.number = select_number(++data->selected.number, data);
	else
		data->selected.number = 0;
	img = mlx_new_image(data->mlx, 200, HEIGHT);
	mlx_put_image_to_window(data->mlx, data->mlx_win, img, 0, 0);
	data->selected.shape = shape;
	mlx_destroy_image(data->mlx, img);
	put_menu(data);
}
