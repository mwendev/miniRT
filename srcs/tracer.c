/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:06:46 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/02/25 17:06:46 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	normalize_vector(float *vector)
{
	float	len;

	len = sqrtf(powf(vector[0], 2) + powf(vector[1], 2) + powf(vector[2], 2));
	vector[0] = vector[0] / len;
	vector[1] = vector[1] / len;
	vector[2] = vector[2] / len;
}

float	*calculate_ray_vector(int i, int j, t_data *data)
{

}

void	calculate_ray(int i, int j, t_data *data)
{
	float	*ray_v;

	ray_v = malloc(sizeof(float) * 3);
	ray_v = calculate_ray_vector(i, j, data);
	free(ray_v);
}

void	fill_image(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->scr_res_h)
	{
		j = -1;
		while (++j < data->scr_res_w)
		{
			calculate_ray(i, j, data);
		}
	}
}
