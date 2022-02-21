/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 08:08:34 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/10/10 08:08:36 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	arr_atoi(char **char_arr, t_window *win, int j)
{
	int		i;
	char	**point_params;
	int		k;

	win->heights[j] = malloc(win->width * sizeof(int));
	win->char_colors[j] = malloc(win->width * sizeof(char *));
	i = -1;
	while (char_arr[++i])
	{
		point_params = ft_split(char_arr[i], ',');
		win->heights[j][i] = ft_atoi(point_params[0]);
		win->char_colors[j][i] = point_params[1];
		k = 2;
		if (point_params[1] != NULL)
		{
			while (point_params[k])
			{
				free(point_params[k]);
				k++;
			}
		}
		free(point_params[0]);
		free(point_params);
	}
}

void	read_file(int fd, t_window *win)
{
	char	*line;
	char	**char_arr;
	int		j;
	int		i;

	j = 0;
	while (get_next_line(fd, &line))
	{
		char_arr = ft_split(line, ' ');
		free(line);
		if (arr_len(char_arr) != win->width)
			emergency_exit(win, j, char_arr);
		arr_atoi(char_arr, win, j);
		j++;
		i = 0;
		while (char_arr[i])
		{
			free(char_arr[i]);
			i++;
		}
		free(char_arr);
	}
	free(line);
}

int	ft_round(double exact_num)
{
	double	int_num;
	double	rest;

	rest = modf(exact_num, &int_num);
	if (rest < 0.5)
		return ((int)floor(exact_num));
	else
		return ((int)ceil(exact_num));
}

void	scale_data(t_window *win)
{
	int		i;
	double	k1;
	double	k2;
	double	scale;

	scale = win->scale_factor * sqrt(2);
	k1 = win->win_width * (1 - 1 / scale) / 2;
	k2 = win->win_width / (win->width * scale);
	win->x_m = malloc(win->width * sizeof(int));
	i = -1;
	while (++i < win->width)
		win->x_m[i] = ft_round(k1 + i * k2);
	k1 = win->win_height * (1 - 1 / scale) / 2;
	k2 = win->win_height / (win->depth * scale);
	win->y_m = malloc(win->depth * sizeof(int));
	i = -1;
	while (++i < win->depth)
		win->y_m[i] = ft_round(k1 + i * k2);
}

void	instructions(t_window *win)
{
	mlx_string_put(win->mlx, win->mlx_win, 20, 50, 65280, "Rotations:");
	mlx_string_put(win->mlx, win->mlx_win, 40, 70, 65280, "arrows");
	mlx_string_put(win->mlx, win->mlx_win, 20, 100, 65280, "Zoom:");
	mlx_string_put(win->mlx, win->mlx_win, 40, 120, 65280, "+ -");
	mlx_string_put(win->mlx, win->mlx_win, 20, 150, 65280, "Translations:");
	mlx_string_put(win->mlx, win->mlx_win, 40, 170, 65280, "up: w, down: s");
	mlx_string_put(win->mlx, win->mlx_win, 40, 190, 65280, "left: a, right: d");
	mlx_string_put(win->mlx, win->mlx_win, 20, 230, 65280, "close window: esc");
}
