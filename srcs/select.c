/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:04:55 by mwen              #+#    #+#             */
/*   Updated: 2022/04/15 11:38:32 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	*select_orient(int axis, t_data *data)
{
	if (data->selected.shape == 'c')
		return (&data->camera.orient[axis]);
	else if (data->selected.shape == 'y')
		return (&data->cylinders->orient[axis]);
	else if (data->selected.shape == 'p')
		return (&data->planes->orient[axis]);
	return (NULL);
}

int	select_number(int selected, t_data *data)
{
	int	i;
	int	ret;

	i = selected;
	ret = 0;
	if (data->selected.shape == 'l' && data->lights)
		while (i-- && data->lights->next && ++ret)
			data->lights = data->lights->next;
	else if (data->selected.shape == 's' && data->spheres)
		while (i-- && data->spheres->next && ++ret)
			data->spheres = data->spheres->next;
	else if (data->selected.shape == 'y' && data->cylinders)
		while (i-- && data->cylinders->next && ++ret)
			data->cylinders = data->cylinders->next;
	else if (data->selected.shape == 'p' && data->planes)
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

	if (data->selected.shape == shape && shape != 'c')
		data->selected.number = select_number(++data->selected.number, data);
	else
	{
		data->selected.number = 0;
		data->selected.shape = shape;
	}
	if ((data->selected.shape == 'l' && !data->lights)
		|| (data->selected.shape == 's' && !data->spheres)
		|| (data->selected.shape == 'y' && !data->cylinders)
		|| (data->selected.shape == 'p' && !data->planes))
		data->selected.shape = 0;
	img = mlx_new_image(data->mlx, 200, HEIGHT);
	mlx_put_image_to_window(data->mlx, data->mlx_win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
	put_menu(data);
}
