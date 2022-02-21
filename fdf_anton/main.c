/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:06:41 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/10/07 16:06:41 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <time.h>

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i++])
		free (arr[i - 1]);
	free (arr);
}

void	initialize_mesh_data(char **argv, t_window *win)
{
	int		fd;
	char	**char_arr;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &line);
	win->depth = 1;
	char_arr = ft_split(line, ' ');
	win->width = 0;
	while (char_arr[win->width])
		win->width++;
	free_arr(char_arr);
	free (line);
	while (get_next_line(fd, &line))
	{
		win->depth++;
		free (line);
	}
	free (line);
	close(fd);
	win->heights = malloc((win->depth + 1) * sizeof(int *));
	win->heights[win->depth] = NULL;
	win->char_colors = malloc((win->depth + 1) * sizeof(int *));
	win->char_colors[win->depth] = NULL;
}

void	free_end(t_window *win)
{
	int	i;
	int	j;

	mlx_destroy_image(win->mlx, win->img);
	mlx_destroy_window(win->mlx, win->mlx_win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win->x_m);
	free(win->y_m);
	i = -1;
	while (++i < win->depth)
	{
		free(win->heights[i]);
		j = -1;
		while (++j < win->width)
			free(win->char_colors[i][j]);
		free(win->char_colors[i]);
	}
	free(win->heights);
	free(win->char_colors);
}

void	initialize_win_params(t_window *win)
{
	win->win_width = 800;
	win->win_height = 600;
	win->angle_h = 45;
	win->angle_v = 35;
	win->pi = 3.1415926535897932384626433;
	win->scale_factor = 1;
	win->offset_x = 0;
	win->offset_y = 0;
}

int	main(int argc, char **argv)
{
	int			fd;
	t_window	win;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd >= 0)
	{
		initialize_win_params(&win);
		initialize_mesh_data(argv, &win);
		read_file(fd, &win);
		scale_data(&win);
		win.mlx = mlx_init();
		win.img = mlx_new_image(win.mlx, win.win_width, win.win_height);
		map_data(&win);
		data_to_img(&win);
		win.mlx_win = mlx_new_window(win.mlx, win.win_width + 150, \
		win.win_height, \
		"Hello world!");
		mlx_put_image_to_window(win.mlx, win.mlx_win, win.img, 150, 0);
		instructions(&win);
		mlx_key_hook(win.mlx_win, key_hook, &win);
		mlx_loop(win.mlx);
	}
	return (0);
}
