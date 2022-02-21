/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:06:36 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/10/07 16:06:38 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <math.h>
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>

typedef struct s_params_struct
{
	size_t	position;
	size_t	chars;
	char	buf[BUFFER_SIZE];
}	t_params;

typedef struct s_params_window
{
	void	*img;
	void	*mlx;
	void	*mlx_win;
	int		win_width;
	int		win_height;
	int		angle_v;
	int		angle_h;
	double	pi;
	int		width;
	int		depth;
	int		**heights;
	char	***char_colors;
	int		*x_m;
	int		*y_m;
	int		**x;
	int		**y;
	int		**colors;
	double	scale_factor;
	int		offset_x;
	int		offset_y;
}	t_window;

int		get_next_line(int fd, char **line);
void	read_file(int fd, t_window *win);
void	scale_data(t_window *win);
int		hex_to_int(char *hex_num);
int		ft_round(double exact_num);
int		**allocate_image(int h, int w);
int		ft_distance(int x1, double x2, int y1, double y2);
void	data_to_img(t_window *win);
void	map_data(t_window *win);
int		ft_interpolate(int p1, int p2, int k, int n);
int		key_hook(int keycode, t_window *win);
void	free_end(t_window *win);
int		arr_len(char **arr);
void	emergency_exit(t_window *win, int j, char **arr);
void	data_to_img_rev(t_window *win);
void	instructions(t_window *win);

#endif
