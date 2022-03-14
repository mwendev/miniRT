/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:19:20 by mwen              #+#    #+#             */
/*   Updated: 2022/03/14 17:25:18 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pixel(t_data *data, int *i)
{
	int	offset;
	char	*dst;

	if (i[1] < WIDTH && i[0] < HEIGHT)
	{
		dst = data->img_addr + i[0] * data->line_len + i[1] * data->bits_per_pixel / 8;
//		offset = (i[0] * data->line_len) + (i[1] * data->bits_per_pixel / 8);
//		data->img_addr[offset] = data->curr_col;
		*(unsigned int *) dst = data->curr_col;
//		data->img_addr[offset] = data->curr_col;
//		data->img_addr[++offset] = data->curr_col >> 8;
//		data->img_addr[++offset] = data->curr_col >> 16;
//		data->img_addr[++offset] = data->curr_col >> 24;
	}
}
