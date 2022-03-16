/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:06:36 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/03/16 20:38:40 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define PI						3.1415926535897932384626433

# define WIDTH					800
# define HEIGHT					600

# include <math.h>
// # include "../minilibx_opengl/mlx.h"
# include <mlx.h>
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "key.h"
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

/*
 * 'c' - camera
 * 'l' - light
 * 's' - sphere
 * 'p' - plane
 * 'y' - cylinder
 * 'o' - cone
 */
typedef struct s_selected
{
	char	shape;
	int		number;
}		t_selected;

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
	float	up[3];
	float	right[3];
	float	fov;
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
	t_selected	selected;
	float		cross_p[3];
	int			curr_col;
	int			curr_col_rgb[3];
	float		nearest_point; // will be considered if intersection occurred
	char		intersection; // indicated that for this pixel intersection occurred
	char		inter_shape; // s - sphere, p - plane, c - cylinder, n - cone
	float		light_dist;
	int			obj_counter;
//	float		scr_dist;
//	int			scr_res_w;
//	int			scr_res_h;
//	int			scr_w;
//	int			scr_h;
//	float		fov;
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
float	angle_vect(float *vect1, float *vect2);
void	camera_up_right(t_data *data);
void	fill_image(t_data *data);
void	cross_product(float *vect1, float *vect2, float *res);
void	normalize_vector(float *vector);
void	put_pixel(t_data *data, int *i);
float	*vector_two_points(float *begin, float *end, float *res);
void	select_shape(char shape, t_data *data);
int		create_trgb(int t, int r, int g, int b);
void	put_menu(t_data *data);

#endif
