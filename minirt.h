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

# define BUFFER_SIZE	50

typedef struct s_params_struct
{
	size_t	position;
	size_t	chars;
	char	buf[BUFFER_SIZE];
}	t_params;

typedef struct s_ambient
{
	float	ratio;
	int		RGB[3]; /* maybe convert to single int color immediately during parsing ? */
}	t_ambient;

typedef struct s_camera
{
	float	coord[3];
	float	orient[3];
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
	void		*img;
	void		*mlx;
	void		*mlx_win;
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	float		scr_dist;
	int			scr_res_w;
	int			scr_res_h;
	int			scr_w;
	int			scr_h;
	float		fov;
}	t_data;

#endif
