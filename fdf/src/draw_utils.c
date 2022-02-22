/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:11:01 by mwen              #+#    #+#             */
/*   Updated: 2021/11/22 11:30:42 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	dup_point(t_point from, t_point *to)
{
	to->x = from.x;
	to->y = from.y;
	to->z = from.z;
	to->color = from.color;
}

int	if_yes_or(int from, int to)
{
	if (from < to)
		return (1);
	else
		return (-1);
}

double	percent(int from, int to, int current)
{
	double	placement;
	double	distance;

	placement = current - from;
	distance = to - from;
	if (distance == 0)
		return (0.0);
	else
		return (placement / distance);
}

int	get_light(int from, int to, double percentage)
{
	return ((int)((1 - percentage) * from + percentage * to));
}

void	process_color(t_point *p, t_point from, t_point to, float *dxy)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (p->color == to.color)
		return ;
	if (dxy[0] > dxy[1])
		percentage = percent(from.x, to.x, p->x);
	else
		percentage = percent(from.y, to.y, p->y);
	red = get_light((from.color >> 16) & 0xFF, (to.color >> 16) & 0xFF,
			percentage);
	green = get_light((from.color >> 8) & 0xFF, (to.color >> 8) & 0xFF,
			percentage);
	blue = get_light((from.color >> 8) & 0xFF, (to.color >> 8) & 0xFF,
			percentage);
	p->color = ((red << 16) | (green << 8) | (blue << 8));
}
