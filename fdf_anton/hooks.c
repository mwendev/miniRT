/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:41:53 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/10/16 19:41:53 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * arrow codes: up 65362 down 65364 left 65361 right 65363
 * printf("%d\n", keycode);
 */

void	redraw(t_window *win)
{
	win->angle_v = win->angle_v % 360;
	win->angle_h = win->angle_h % 360;
	mlx_destroy_image(win->mlx, win->img);
	win->img = mlx_new_image(win->mlx, win->win_width, win->win_height);
	map_data(win);
	if (win->angle_h <= 90 || win->angle_h > 270)
	{
		if (win->angle_v < 90 || win->angle_v >= 270)
			data_to_img(win);
		else
			data_to_img_rev(win);
	}
	else
	{
		if (win->angle_v < 90 || win->angle_v >= 270)
			data_to_img_rev(win);
		else
			data_to_img(win);
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img, 150, 0);
}

void	rotations(int keycode, t_window *win)
{
	if (keycode == 65361)
	{
		win->angle_h += 5;
		redraw(win);
	}
	else if (keycode == 65363)
	{
		win->angle_h -= 5;
		redraw(win);
	}
	else if (keycode == 65362)
	{
		win->angle_v -= 5;
		redraw(win);
	}
	else if (keycode == 65364)
	{
		win->angle_v += 5;
		redraw(win);
	}
}

void	magnification(int keycode, t_window *win)
{
	if (keycode == 65451)
		win->scale_factor /= 1.05;
	else
		win->scale_factor *= 1.05;
	mlx_destroy_image(win->mlx, win->img);
	win->img = mlx_new_image(win->mlx, win->win_width, win->win_height);
	free(win->x_m);
	free(win->y_m);
	scale_data(win);
	map_data(win);
	data_to_img(win);
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img, 150, 0);
}

/*
 * w - 119
 * a - 97
 * s - 115
 * d - 100
 */

void	translation(int keycode, t_window *win)
{
	if (keycode == 119)
		win->offset_y -= 10;
	else if (keycode == 97)
		win->offset_x -= 10;
	else if (keycode == 115)
		win->offset_y += 10;
	else if (keycode == 100)
		win->offset_x += 10;
	mlx_destroy_image(win->mlx, win->img);
	win->img = mlx_new_image(win->mlx, win->win_width, win->win_height);
	map_data(win);
	data_to_img(win);
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img, 150, 0);
}

int	key_hook(int keycode, t_window *win)
{
	if (keycode == 65307)
	{
		free_end(win);
		exit(0);
	}
	else if (keycode == 65361 || keycode == 65363 || keycode == 65362 || \
	keycode == 65364 )
		rotations(keycode, win);
	else if (keycode == 65451 || keycode == 65453)
		magnification(keycode, win);
	else if (keycode == 119 || keycode == 97 || keycode == 115 || \
	keycode == 100)
		translation(keycode, win);
	return (0);
}
