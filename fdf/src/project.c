/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:16:24 by mwen              #+#    #+#             */
/*   Updated: 2021/11/21 14:28:39 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	project_iso(t_point *p)
{
	int	x;
	int	y;

	x = p->x;
	y = p->y;
	p->x = (x - y) * cos(0.523599);
	p->y = (x + y) * sin(0.523599) - p->z;
}

void	rotate_x(t_point *p, double rx)
{
	int	y;

	y = p->y;
	p->y = y * cos(rx) + p->z * sin(rx);
	p->z = -y * sin(rx) + p->z * cos(rx);
}

void	rotate_y(t_point *p, double ry)
{
	int	x;

	x = p->x;
	p->x = x * cos(ry) + p->z * sin(ry);
	p->z = -x * sin(ry) + p->z * cos(ry);
}

void	rotate_z(t_point *p, double rz)
{
	int	x;
	int	y;

	x = p->x;
	y = p->y;
	p->x = x * cos(rz) - y * sin(rz);
	p->y = x * sin(rz) + y * cos(rz);
}

t_point	project(t_fdf *data, int x, int y)
{
	t_point	p;
	int		menu_wid;

	menu_wid = WIDTH / 4;
	dup_point(data->map->p[y][x], &p);
	p.x *= data->cam->zoom;
	p.y *= data->cam->zoom;
	p.z *= data->cam->zoom / data->cam->move_z;
	p.x -= (data->map->wid * data->cam->zoom) / 2;
	p.y -= (data->map->hgt * data->cam->zoom) / 2;
	rotate_x(&p, data->cam->rx);
	rotate_y(&p, data->cam->ry);
	rotate_z(&p, data->cam->rz);
	if (data->cam->projection == 1)
		project_iso(&p);
	p.x += (WIDTH - menu_wid) / 2 + data->cam->move_x + menu_wid;
	p.y += (HEIGHT + data->map->hgt * data->cam->zoom) / 2 + data->cam->move_y;
	return (p);
}
