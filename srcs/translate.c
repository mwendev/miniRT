/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:53:10 by mwen              #+#    #+#             */
/*   Updated: 2022/04/10 18:50:36 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	operate(char operation, int axis, t_data *data)
{
	if (operation == '-')
	{
		if (data->selected.shape == 'l')
			data->lights->coord[axis]--;
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
			data->lights->coord[axis]++;
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

void	distribute(t_data *data)
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
}

void	translate(int key, t_data *data)
{
	distribute(data);
	if (key == MAC_1 || key == XK_1)
		operate('-', 0, data);
	else if (key == MAC_E || key == XK_e)
		operate('+', 0, data);
	else if (key == MAC_3 || key == XK_3)
		operate('+', 1, data);
	else if (key == MAC_Q || key == XK_q)
		operate('-', 1, data);
	else if (key == MAC_2 || key == XK_2)
		operate('+', 2, data);
	else if (key == MAC_W || key == XK_w)
		operate('-', 2, data);
	rewind_link(data);
	fill_image(data);
}
