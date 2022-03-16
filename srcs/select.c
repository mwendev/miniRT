/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:04:55 by mwen              #+#    #+#             */
/*   Updated: 2022/03/16 13:08:42 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select(char shape, t_data *data)
{
	if (data->selected.shape == shape && shape != 'c')
		data->selected.number++;
	else
		data->selected.number = 0;
	data->selected.shape = shape;
}