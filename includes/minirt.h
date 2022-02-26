/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:06:36 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/02/26 01:10:24 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <math.h>
# include "../minilibx_opengl/mlx.h"
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

typedef struct s_ambient
{
	float			ratio;
	int				RGB[3];
	unsigned long	color;
}	t_ambient;

typedef struct s_camera
{
	float	coord[3];
	float	orient[3];
	int		fov;
}	t_camera;

typedef struct s_light
{
	float	coord[3];
	float	orient[3];
	int		RGB[3]; /* same as ambient */
}	t_light;

typedef struct s_sphere
{
	float	coord[3];
	float	diameter;
	int		RGB[3]; /* same as ambient */
}	t_sphere;

typedef struct s_plane
{
	float	coord[3];
	float	orient[3];
	int		RGB[3]; /* same as ambient */
}	t_plane;

typedef struct s_cylinder
{
	float	coord[3];
	float	orient[3];
	float	diameter;
	float	height;
	int		RGB[3]; /* same as ambient */
}	t_cylinder;

typedef struct s_data
{
	void	*img;
	void	*mlx;
	void	*mlx_win;
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}	t_data;

int		parse(char	*file, t_data *data);
int		terminate(t_data *data, char *msg, int if_exit);
int		ft_atof(char *line, float *f, int if_free);
char	*parse_information(char *line, int *i);
int		parse_color(char *line, int *rgb, unsigned long color);
int		parse_farray(char *line, float *array, int orientation);

#endif
