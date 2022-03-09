/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:19:20 by mwen              #+#    #+#             */
/*   Updated: 2022/03/09 19:26:32 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	put_pixel(t_data *data, int *i)
{
	int	offset;

	if (i[1] < WIDTH && i[0] < HEIGHT)
	{
		offset = (i[0] * data->line_len) + (i[1] * data->bits_per_pixel / 8);
		data->img_addr[offset] = data->curr_col;
	}
}
