/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:44:06 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/10/16 17:44:16 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * img_par[0] - bits per pixel
 * img_par[1] - line length
 * img_par[2] - endian
 * p[0] - number of points between 2 vertices
 * p[1] - loop counter
 * p[2] - x coordinate of the point on the line
 * p[3] - y coordinate of the point on the line
 * p[4] - resulting color
 */

void	line_to_img_vertical(t_window *win, int i, int j)
{
	int		p[5];
	int		color;
	char	*addr;
	char	*dst;
	int		img_par[3];

	addr = mlx_get_data_addr(win->img, &img_par[0], &img_par[1], &img_par[2]);
	p[0] = ft_distance(win->x[i][j], win->x[i + 1][j], win->y[i][j], \
	win->y[i + 1][j]);
	p[1] = -1;
	while (++p[1] < p[0])
	{
		p[2] = ft_interpolate(win->x[i][j], win->x[i + 1][j], p[1], p[0]);
		p[3] = ft_interpolate(win->y[i][j], win->y[i + 1][j], p[1], p[0]);
		if (p[2] >= 0 && p[2] < win->win_width && p[3] >= 0 && \
		p[3] < win->win_height)
		{
			color = ft_interpolate(win->colors[i][j], \
			win->colors[i + 1][j], p[1], p[0]);
			dst = addr + p[3] * img_par[1] + p[2] * img_par[0] / 8;
			*(unsigned int *) dst = color;
		}
	}
}

void	line_to_img_horizontal(t_window *win, int i, int j)
{
	int		p[5];
	int		color;
	char	*addr;
	char	*dst;
	int		img_par[3];

	addr = mlx_get_data_addr(win->img, &img_par[0], &img_par[1], &img_par[2]);
	p[0] = ft_distance(win->x[i][j], win->x[i][j + 1], win->y[i][j], \
	win->y[i][j + 1]);
	p[1] = -1;
	while (++p[1] < p[0])
	{
		p[2] = ft_interpolate(win->x[i][j], win->x[i][j + 1], p[1], p[0]);
		p[3] = ft_interpolate(win->y[i][j], win->y[i][j + 1], p[1], p[0]);
		if (p[2] >= 0 && p[2] < win->win_width && p[3] >= 0 && \
		p[3] < win->win_height)
		{
			color = ft_interpolate(win->colors[i][j], \
			win->colors[i][j + 1], p[1], p[0]);
			dst = addr + p[3] * img_par[1] + p[2] * img_par[0] / 8;
			*(unsigned int *) dst = color;
		}
	}
}

void	free_mem_interm(t_window *win)
{
	int	i;

	i = -1;
	while (++i < win->depth)
	{
		free(win->x[i]);
		free(win->y[i]);
		free(win->colors[i]);
	}
	free(win->x);
	free(win->y);
	free(win->colors);
}

void	data_to_img(t_window *win)
{
	int	i;
	int	j;

	i = -1;
	while (++i < win->depth - 1)
	{
		j = -1;
		while (++j < win->width - 1)
		{
			line_to_img_horizontal(win, i, j);
			line_to_img_vertical(win, i, j);
		}
		line_to_img_vertical(win, i, j);
	}
	j = -1;
	while (++j < win->width - 1)
		line_to_img_horizontal(win, i, j);
	free_mem_interm(win);
}

void	data_to_img_rev(t_window *win)
{
	int	i;
	int	j;

	i = win->depth - 1;
	j = win->width - 1;
	while (--j >= 0)
		line_to_img_horizontal(win, i, j);
	while (--i >= 0)
	{
		j = win->width - 1;
		line_to_img_vertical(win, i, j);
		while (--j >= 0)
		{
			line_to_img_horizontal(win, i, j);
			line_to_img_vertical(win, i, j);
		}
	}
	free_mem_interm(win);
}
