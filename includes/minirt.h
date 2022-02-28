/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:06:36 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/02/26 23:18:53 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH					800
# define HEIGHT					600

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

# include <math.h>
# include "../minilibx_opengl/mlx.h"
//# include <mlx.h>
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h>

typedef struct s_params_struct
{
	size_t	position;
	size_t	chars;
	char	buf[BUFFER_SIZE];
}	t_params;

typedef struct s_mouse
{
	int	pressed;
	int	x;
	int	y;
	int	prev_x;
	int	prev_y;
}		t_mouse;

typedef struct s_ambient
{
	float			ratio;
	int				rgb[3];
	unsigned long	color;
}	t_ambient;

typedef struct s_camera
{
	float	coord[3];
	float	orient[3];
	int		fov;
	int		rotation;
}	t_camera;

typedef struct s_light
{
	float			coord[3];
	float			ratio;
	int				rgb[3];
	unsigned long	color;
	struct s_light	*next;
	struct s_light	*prev;
}	t_light;

typedef struct s_sphere
{
	float			coord[3];
	float			diameter;
	int				rgb[3];
	unsigned long	color;
	struct s_sphere	*next;
	struct s_sphere	*prev;
}	t_sphere;

typedef struct s_plane
{
	float			coord[3];
	float			orient[3];
	int				rgb[3];
	int				rotation[3];
	unsigned long	color;
	struct s_plane	*next;
	struct s_plane	*prev;
}	t_plane;

typedef struct s_cylinder
{
	float				coord[3];
	float				orient[3];
	float				diameter;
	float				height;
	int					rgb[3];
	int					rotation[3];
	unsigned long		color;
	struct s_cylinder	*next;
	struct s_cylinder	*prev;
}	t_cylinder;

typedef struct s_data
{
	void		*img;
	void		*mlx;
	void		*mlx_win;
	char		*img_addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	t_mouse		*mouse;
	float		scr_dist;
	int			scr_res_w;
	int			scr_res_h;
	int			scr_w;
	int			scr_h;
	float		fov;
}	t_data;

int		parse(char	*file, t_data *data);
int		terminate(t_data *data, char *msg, int if_exit);
int		stof(char *str, float *f, int if_free);
char	*parse_info(char *str, int *i);
int		parse_color(char *str, int *rgb, unsigned long *color);
int		parse_farray(char *str, float *array, int orientation);
int		parse_light(char *str, t_data *data, int type, t_light *new);
int		parse_sp(char *str, t_data *data, int type, t_sphere *new);
int		parse_pl(char *str, t_data *data, int type, t_plane *new);
int		parse_cy(char *str, t_data *data, int type, t_cylinder *new);
int		shut_down(t_data *data);
int		listen_key(int key, t_data *data);
int		listen_mouse_moved(int x, int y, t_data *data);
int		listen_mouse_released(int button, int x, int y, t_data *data);
int		listen_mouse_pressed(int button, int x, int y, t_data *data);


#endif
