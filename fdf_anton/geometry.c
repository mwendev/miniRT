/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:47:27 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/10/16 17:47:40 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * angles[0] - horizontal rotation angle in radian
 * angles[1] - vertical rotation angle in radian
 * angles[2] - initial angle of the vector to the point respective to center of
 * rotation (in radian)
 * angles[3] - resulting horizontal rotation angle in radian
 */

void	project_isometric(int *c, t_window *win)
{
	double	angles[4];
	double	radius;
	double	half_h;
	double	half_w;

	half_h = (double)win->win_height / 2;
	half_w = (double)win->win_width / 2;
	radius = ft_distance(win->x_m[c[3]], half_w, win->y_m[c[2]], half_h);
	angles[0] = (double)win->angle_h / 180 * win->pi;
	angles[1] = (double)win->angle_v / 180 * win->pi;
	angles[2] = atan2(win->y_m[c[2]] - half_h, win->x_m[c[3]] - half_w);
	angles[3] = angles[2] + angles[0];
	if (angles[3] < -win->pi)
		angles[3] += win->pi * 2;
	if (angles[3] > win->pi)
		angles[3] -= win->pi * 2;
	c[0] = ft_round(radius * cos(angles[3])) + ft_round(half_w);
	c[1] = ft_round(radius * sin(angles[3])) + ft_round(half_h);
	if (c[1] < half_h)
		c[1] = ft_round(c[1] + (half_h - c[1]) * (1 - sin(angles[1])));
	else
		c[1] = ft_round(c[1] - (c[1] - half_h) * (1 - sin(angles[1])));
	c[1] -= ft_round((double)win->heights[c[2]][c[3]] * cos(angles[1]) \
	/ win->scale_factor);
}

/*
 * c[0] - x_m, c[1] - y_m, c[2] - i, c[3] - j, c[4] - color
 */
void	map_data(t_window *win)
{
	int	c[5];

	win->depth = win->depth;
	win->width = win->width;
	win->x = allocate_image(win->depth, win->width);
	win->y = allocate_image(win->depth, win->width);
	win->colors = allocate_image(win->depth, win->width);
	c[2] = -1;
	while (++c[2] < win->depth)
	{
		c[3] = -1;
		while (++c[3] < win->width)
		{
			if (win->char_colors[c[2]][c[3]] == NULL)
				c[4] = hex_to_int("0xFFFFFF");
			else
				c[4] = hex_to_int(win->char_colors[c[2]][c[3]]);
			project_isometric(c, win);
			win->x[c[2]][c[3]] = c[0] + win->offset_x;
			win->y[c[2]][c[3]] = c[1] + win->offset_y;
			win->colors[c[2]][c[3]] = c[4];
		}
	}
}
