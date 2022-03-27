/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:53:10 by mwen              #+#    #+#             */
/*   Updated: 2022/03/17 20:34:51 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	operate(char operation, int axis, t_data *data)
{
	if (operation == '-')
	{
		if (data->selected.shape == 'l')
			data->lights->coord[axis] -= 80;
		else if (data->selected.shape == 's')
			data->spheres->coord[axis]--;
		else if (data->selected.shape == 'y')
			data->cylinders->coord[axis]--;
		else if (data->selected.shape == 'p')
			data->planes->coord[axis]--;
		else if (data->selected.shape == 'c')
			data->camera.coord[axis]--;
	}
	if (operation == '+')
	{
		if (data->selected.shape == 'l')
			data->lights->coord[axis] += 80;
		else if (data->selected.shape == 's')
			data->spheres->coord[axis]++;
		else if (data->selected.shape == 'y')
			data->cylinders->coord[axis]++;
		else if (data->selected.shape == 'p')
			data->planes->coord[axis]++;
		else if (data->selected.shape == 'c')
			data->camera.coord[axis]++;
	}
}

void	distribute(char operation, int axis, t_data *data)
{
	int	i;

	i = data->selected.number;
	if (data->selected.shape == 'l')
		while (i--)
			data->lights = data->lights->next;
	else if (data->selected.shape == 's')
		while (i--)
			data->spheres = data->spheres->next;
	else if (data->selected.shape == 'y')
		while (i--)
			data->cylinders = data->cylinders->next;
	else if (data->selected.shape == 'p')
		while (i--)
			data->planes = data->planes->next;
	// else if (data->selected.shape == 'o')
	operate(operation, axis, data);
	rewind_link(data);
	fill_image(data);
}

void	translate(int key, t_data *data)
{
	if (key == MAC_1 || key == XK_1)
		distribute('-', 0, data);
	else if (key == MAC_E || key == XK_e)
		distribute('+', 0, data);
	else if (key == MAC_3 || key == XK_3)
		distribute('+', 1, data);
	else if (key == MAC_Q || key == XK_q)
		distribute('-', 1, data);
	else if (key == MAC_2 || key == XK_2)
		distribute('+', 2, data);
	else if (key == MAC_W || key == XK_w)
		distribute('+', 2, data);
}
