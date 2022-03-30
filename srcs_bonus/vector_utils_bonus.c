/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:43:49 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/14 17:25:25 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

float	dot_prod(float *vect1, float *vect2)
{
	return (vect1[0] * vect2[0] + vect1[1] * vect2[1] + vect1[2] * vect2[2]);
}

float	angle_vect(float *vect1, float *vect2)
{
	float	mod_vect1;
	float	mod_vect2;

	mod_vect1 = sqrtf(powf(vect1[0], 2) + powf(vect1[1], 2)
			+ powf(vect1[2], 2));
	mod_vect2 = sqrtf(powf(vect2[0], 2) + powf(vect2[1], 2)
			+ powf(vect2[2], 2));
	return (acosf(dot_prod(vect1, vect2) / (mod_vect1 * mod_vect2)));
}

void	cross_product(float *vect1, float *vect2, float *res)
{
	res[0] = vect1[1] * vect2[2] - vect1[2] * vect2[1];
	res[1] = vect1[2] * vect2[0] - vect1[0] * vect2[2];
	res[2] = vect1[0] * vect2[1] - vect1[1] * vect2[0];
}

void	normalize_vector(float *vector)
{
	float	len;

	len = sqrtf(powf(vector[0], 2) + powf(vector[1], 2) + powf(vector[2], 2));
	vector[0] = vector[0] / len;
	vector[1] = vector[1] / len;
	vector[2] = vector[2] / len;
}

float	*vector_two_points(float *begin, float *end, float *res)
{
	res[0] = end[0] - begin[0];
	res[1] = end[1] - begin[1];
	res[2] = end[2] - begin[2];
	return (res);
}
