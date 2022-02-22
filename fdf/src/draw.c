/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:43:15 by mwen              #+#    #+#             */
/*   Updated: 2021/11/22 02:27:44 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_background(t_fdf *data)
{
	int	*image;
	int	i;
	int	menu_wid;

	image = (int *)data->img_addr;
	i = -1;
	menu_wid = WIDTH / 4;
	while (++i < WIDTH * HEIGHT)
	{
		if (i % WIDTH < menu_wid)
			image[i] = MENU_COL;
		else
			image[i] = BKG_COL;
	}
}

void	draw_pixel(t_fdf *data, t_point p)
{
	int	offset;
	int	menu_wid;

	menu_wid = WIDTH / 4;
	if (p.x >= menu_wid && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT)
	{
		offset = (p.y * data->line_len) + (p.x * data->bits_per_pixel / 8);
		data->img_addr[offset] = p.color;
		data->img_addr[++offset] = p.color >> 8;
		data->img_addr[++offset] = p.color >> 16;
	}
}

void	draw_line(t_fdf *data, t_point from, t_point to)
{
	float	dxy[4];
	int		fraction;
	t_point	dup;

	dxy[0] = fabs((float)to.x - (float)from.x);
	dxy[1] = fabs((float)to.y - (float)from.y);
	dxy[2] = if_yes_or(from.x, to.x);
	dxy[3] = if_yes_or(from.y, to.y);
	fraction = dxy[0] - dxy[1];
	dup_point(from, &dup);
	while (dup.x != to.x || dup.y != to.y)
	{
		process_color(&dup, from, to, dxy);
		draw_pixel(data, dup);
		if (fraction * 2 > -dxy[1])
		{
			fraction -= dxy[1];
			dup.x += dxy[2];
		}
		else if (fraction * 2 < dxy[0])
		{
			fraction += dxy[0];
			dup.y += dxy[3];
		}
	}
}

void	draw_menu(t_fdf *data)
{
	int		y;
	int		menu_wid;
	void	*m;
	void	*w;

	y = 0;
	m = data->mlx;
	w = data->win;
	menu_wid = WIDTH / 4;
	mlx_string_put(m, w, menu_wid / 3, y += 20, TEXT_COL, "You can:");
	mlx_string_put(m, w, 15, y += 25, TEXT_COL, "zoom:");
	mlx_string_put(m, w, 50, y += 25, TEXT_COL, "scroll or press +/-");
	mlx_string_put(m, w, 15, y += 25, TEXT_COL, "move:");
	mlx_string_put(m, w, 50, y += 25, TEXT_COL, "press arrows");
	mlx_string_put(m, w, 15, y += 25, TEXT_COL, "flatten:");
	mlx_string_put(m, w, 50, y += 25, TEXT_COL, "press Z/X");
	mlx_string_put(m, w, 15, y += 25, TEXT_COL, "rotate:");
	mlx_string_put(m, w, 50, y += 25, TEXT_COL, "press W/S/A/D/Q/E");
	mlx_string_put(m, w, 50, y += 25, TEXT_COL, "mouse left click and move");
	mlx_string_put(m, w, 15, y += 25, TEXT_COL, "change projection:");
	mlx_string_put(m, w, 50, y += 25, TEXT_COL, "press I/P");
	mlx_string_put(m, w, 15, y += 25, TEXT_COL, "Mark me excellent :3!");
}

void	draw(t_fdf *data)
{
	int	x;
	int	y;

	draw_background(data);
	y = -1;
	while (++y < data->map->hgt)
	{
		x = -1;
		while (++x < data->map->wid)
		{
			if (y != data->map->hgt - 1)
				draw_line(data, project(data, x, y),
					project(data, x, y + 1));
			if (x != data->map->wid - 1)
				draw_line(data, project(data, x, y),
					project(data, x + 1, y));
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	draw_menu(data);
}
