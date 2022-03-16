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
	if (data->selected.shape == shape && shape != 'c')
		data->selected.number++;
	else
		data->selected.number = 0;
	data->selected.shape = shape;
	put_menu(data);
}
