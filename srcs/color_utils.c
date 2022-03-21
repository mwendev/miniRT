/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:37:40 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/17 14:37:44 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	mix_ambient(t_data *data, int *rgb, int *obj_rgb, float tr)
{
	data->curr_col_rgb[0] = (int)((float)rgb[0] * tr * (float)obj_rgb[0] / 255);
	if (data->curr_col_rgb[0] > 255)
		data->curr_col_rgb[0] = 255;
	data->curr_col_rgb[1] = (int)((float)rgb[1] * tr * (float)obj_rgb[1] / 255);
	if (data->curr_col_rgb[1] > 255)
		data->curr_col_rgb[1] = 255;
	data->curr_col_rgb[2] = (int)((float)rgb[2] * tr * (float)obj_rgb[2] / 255);
	if (data->curr_col_rgb[2] > 255)
		data->curr_col_rgb[2] = 255;
}

void	mix_light(t_data *data, int *rgb, float angle, float tr)
{
	data->curr_col_rgb[0] = data->curr_col_rgb[0]
			+ (int)((float)rgb[0] * fabs((double)cosf(angle)) * tr);
	if (data->curr_col_rgb[0] > 255)
		data->curr_col_rgb[0] = 255;
	data->curr_col_rgb[1] = data->curr_col_rgb[1]
			+ (int)((float)rgb[1] * fabs((double)cosf(angle)) * tr);
	if (data->curr_col_rgb[1] > 255)
		data->curr_col_rgb[1] = 255;
	data->curr_col_rgb[2] = data->curr_col_rgb[2]
			+ (int)((float)rgb[2] * fabs((double)cosf(angle)) * tr);
	if (data->curr_col_rgb[2] > 255)
		data->curr_col_rgb[2] = 255;
}
