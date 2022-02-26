/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:11:07 by mwen              #+#    #+#             */
/*   Updated: 2022/02/26 16:01:52 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ERR_USAGE				"Error: Usage: ./fdf FILE_NAME.fdf"
# define ERR_INIT_DATA			"Failed to init data"
# define ERR_INIT_MAP			"Failed to init map data"
# define ERR_INIT_POINT			"Failed to init coordination data"
# define ERR_INIT_COLOR			"Failed to init to assign color"
# define ERR_INIT_CAM			"Failed to init camera data"
# define ERR_INIT_MLX			"Failed to connect to the graphical system"
# define ERR_INIT_WINDOW		"Failed to create a new window"
# define ERR_INIT_IMG			"Failed to create image"
# define ERR_INIT_MOUSE			"Failed to init mouse data"
# define ERR_OFILE				"Failed to open fdf file"

# define WIDTH					1200
# define HEIGHT					750

# define ARROW_UP				126
# define ARROW_DOWN				125
# define ARROW_LEFT				123
# define ARROW_RIGHT			124

# define MAIN_PAD_ESC			53
# define MAIN_PAD_W				13
# define MAIN_PAD_S				1
# define MAIN_PAD_A				0
# define MAIN_PAD_D				2
# define MAIN_PAD_Q				12
# define MAIN_PAD_E				14
# define MAIN_PAD_I				34
# define MAIN_PAD_P				35
# define MAIN_PAD_Z				6
# define MAIN_PAD_X				7
# define MAIN_PAD_PLUS			24
# define MAIN_PAD_MINUS			27

# define MOUSE_LEFT_BUTTON		1
# define MOUSE_SCROLL_UP		4
# define MOUSE_SCROLL_DOWN		5

# define LX_ARROW_UP			98
# define LX_ARROW_DOWN			104
# define LX_ARROW_LEFT			100
# define LX_ARROW_RIGHT			102

# define LX_MAIN_PAD_ESC		9
# define LX_MAIN_PAD_W			25
# define LX_MAIN_PAD_S			39
# define LX_MAIN_PAD_A			38
# define LX_MAIN_PAD_D			40

# define LX_MAIN_PAD_Q			24
# define LX_MAIN_PAD_E			26
# define LX_MAIN_PAD_I			31
# define LX_MAIN_PAD_P			33
# define LX_MAIN_PAD_Z			52
# define LX_MAIN_PAD_X			53
# define LX_MAIN_PAD_PLUS		24
# define LX_MAIN_PAD_MINUS		21

# define LX_MOUSE_LEFT_BUTTON	108
# define LX_MOUSE_SCROLL_UP		234
# define LX_MOUSE_SCROLL_DOWN	233

# define MENU_COL				0x1E1E1E
# define BKG_COL				0x222222
# define GROUND_COL				0xFFFFFF
# define SLOP_COL				0xF3AF3D
# define SLOPP_COL				0xEF8633
# define PEAK_COL				0x9A1F6A
# define TEXT_COL				0xEAEAEA

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct s_mouse
{
	int	pressed;
	int	x;
	int	y;
	int	prev_x;
	int	prev_y;
}		t_mouse;

typedef struct s_cam
{
	int		zoom;
	int		move_x;
	int		move_y;
	float	move_z;
	double	rx;
	double	ry;
	double	rz;
	int		projection;
}			t_cam;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_map
{
	int			wid;
	int			hgt;
	t_point		**p;
}				t_map;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	t_map	*map;
	t_cam	*cam;
	t_mouse	*mouse;
}			t_fdf;

void	init_data(t_fdf *data, char *file_name);
void	terminate(char	*err_msg, t_fdf *data);
void	free_split(char **str);
void	read_map(t_fdf *data, char *file_name);
void	draw(t_fdf *data);
t_point	project(t_fdf *data, int x, int y);
void	dup_point(t_point from, t_point *to);
int		listen_key(int key, t_fdf *data);
int		listen_mouse_pressed(int button, int x, int y, t_fdf *data);
int		listen_mouse_released(int button, int x, int y, t_fdf *data);
int		listen_mouse_moved(int x, int y, t_fdf *data);
void	rotate(int key, t_fdf *data);
void	move(int key, t_fdf *data);
void	flatten(int key, t_fdf *data);
void	zoom(int key, t_fdf *data);
void	change_projection(int key, t_fdf *data);
int		if_yes_or(int from, int to);
void	process_color(t_point *p, t_point from, t_point to, float *dxy);
double	percent(int from, int to, int current);
void	assign_color(t_fdf *data);

#endif