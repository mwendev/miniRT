/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:53:10 by mwen              #+#    #+#             */
/*   Updated: 2022/04/15 12:29:42 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	operate(char operation, int axis, t_data *data)
{
	if (operation == '-' && data->selected.shape == 'l')
		data->lights->coord[axis]--;
	else if (operation == '-' && data->selected.shape == 's')
		data->spheres->coord[axis]--;
	else if (operation == '-' && data->selected.shape == 'y')
		data->cylinders->coord[axis]--;
	else if (operation == '-' && data->selected.shape == 'p')
		data->planes->coord[axis]--;
	else if (operation == '-' && data->selected.shape == 'c')
		data->camera.coord[axis]--;
	else if (operation == '+' && data->selected.shape == 'l')
		data->lights->coord[axis]++;
	else if (operation == '+' && data->selected.shape == 's')
		data->spheres->coord[axis]++;
	else if (operation == '+' && data->selected.shape == 'y')
		data->cylinders->coord[axis]++;
	else if (operation == '+' && data->selected.shape == 'p')
		data->planes->coord[axis]++;
	else if (operation == '+' && data->selected.shape == 'c')
		data->camera.coord[axis]++;
}

int	distribute(t_data *data)
{
	int	i;
	int	ret;

	i = data->selected.number;
	ret = 0;
	if (data->selected.shape == 'l' && data->lights)
		while (i--)
			data->lights = data->lights->next;
	else if (data->selected.shape == 's' && data->spheres)
		while (i--)
			data->spheres = data->spheres->next;
	else if (data->selected.shape == 'y' && data->cylinders)
		while (i--)
			data->cylinders = data->cylinders->next;
	else if (data->selected.shape == 'p' && data->planes)
		while (i--)
			data->planes = data->planes->next;
	else if (data->selected.shape == 'c')
		ret = 0;
	else
		ret = 1;
	return (ret);
}

void	translate(int key, t_data *data)
{
	if (distribute(data))
		return ;
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
