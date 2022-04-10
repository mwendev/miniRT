/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 21:46:54 by mwen              #+#    #+#             */
/*   Updated: 2022/03/20 21:52:25 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	resize(int key, t_data *data)
{
	distribute(data);
	if (data->selected.shape == 's')
	{
		if (key == MAC_PLUS || key == XK_plus)
			data->spheres->diameter++;
		else if (key == MAC_MINUS || key == XK_minus)
			data->spheres->diameter--;
	}
	else if (data->selected.shape == 'y')
	{
		if (key == MAC_PLUS || key == XK_plus)
		{
			data->cylinders->diameter++;
			data->cylinders->height++;
		}
		else if (key == MAC_MINUS || key == XK_minus)
		{
			data->cylinders->diameter--;
			data->cylinders->height--;
		}
	}
	rewind_link(data);
	fill_image(data);
}
