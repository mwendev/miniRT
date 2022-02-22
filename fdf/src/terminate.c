/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:21:32 by mwen              #+#    #+#             */
/*   Updated: 2021/11/22 11:53:14 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_split(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	free_double(t_point **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	error_write(char *err_msg, int i)
{
	perror(err_msg);
	return (i);
}

void	free_fdf(t_fdf *data)
{
	if (data->map)
	{
		if (data->map->p)
			free_double(data->map->p);
		free(data->map);
	}
	if (data->cam)
		free(data->cam);
	if (data->mouse)
		free(data->mouse);
	if (data->mlx && data->win)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
	}
	free(data);
}

void	terminate(char	*err_msg, t_fdf *data)
{
	if (!data)
		exit (error_write(err_msg, 1));
	free_fdf(data);
	if (!err_msg)
		exit (0);
	if (ft_strnstr(err_msg, ERR_INIT_MAP, ft_strlen(err_msg)))
		exit (error_write(err_msg, 2));
	if (ft_strnstr(err_msg, ERR_OFILE, ft_strlen(err_msg)))
		exit (error_write(err_msg, 3));
	if (ft_strnstr(err_msg, ERR_INIT_POINT, ft_strlen(err_msg)))
		exit (error_write(err_msg, 4));
	if (ft_strnstr(err_msg, ERR_INIT_COLOR, ft_strlen(err_msg)))
		exit (error_write(err_msg, 5));
	if (ft_strnstr(err_msg, ERR_INIT_CAM, ft_strlen(err_msg)))
		exit (error_write(err_msg, 6));
	if (ft_strnstr(err_msg, ERR_INIT_MLX, ft_strlen(err_msg)))
		exit (error_write(err_msg, 7));
	if (ft_strnstr(err_msg, ERR_INIT_WINDOW, ft_strlen(err_msg)))
		exit (error_write(err_msg, 8));
	if (ft_strnstr(err_msg, ERR_INIT_MOUSE, ft_strlen(err_msg)))
		exit (error_write(err_msg, 9));
}
