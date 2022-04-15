/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:41:02 by mwen              #+#    #+#             */
/*   Updated: 2022/04/15 10:25:58 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_cylinder(t_data *data)
{
	t_cylinder	*tmp;

	if (!data->cylinders)
		return ;
	while (data->cylinders->next)
		data->cylinders = data->cylinders->next;
	while (data->cylinders->prev)
	{
		tmp = data->cylinders->prev;
		free(data->cylinders);
		data->cylinders = tmp;
	}
	free(data->cylinders);
	data->cylinders = NULL;
}

void	free_plane(t_data *data)
{
	t_plane	*tmp;

	if (!data->planes)
		return ;
	while (data->planes->next)
		data->planes = data->planes->next;
	while (data->planes->prev)
	{
		tmp = data->planes->prev;
		free(data->planes);
		data->planes = tmp;
	}
	free(data->planes);
	data->planes = NULL;
}

void	free_spheres(t_data *data)
{
	t_sphere	*tmp;

	if (!data->spheres)
		return ;
	while (data->spheres->next)
		data->spheres = data->spheres->next;
	while (data->spheres->prev)
	{
		tmp = data->spheres->prev;
		free(data->spheres);
		data->spheres = tmp;
	}
	free(data->spheres);
	data->spheres = NULL;
}

void	free_light(t_data *data)
{
	t_light	*tmp;

	if (!data->lights)
		return ;
	while (data->lights->next)
		data->lights = data->lights->next;
	while (data->lights->prev)
	{
		tmp = data->lights->prev;
		free(data->lights);
		data->lights = tmp;
	}
	free(data->lights);
	data->lights = NULL;
}

int	terminate(t_data *data, char *msg, int if_exit)
{
	if (data)
	{
		if (data->mlx && data->mlx_win)
		{
			mlx_destroy_image(data->mlx, data->img);
			mlx_destroy_window(data->mlx, data->mlx_win);
			// mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
		if (data->mouse)
			free(data->mouse);
		free_light(data);
		free_spheres(data);
		free_plane(data);
		free_cylinder(data);
	}
	if (msg)
		perror(msg);
	if (if_exit)
		exit (if_exit);
	return (1);
}
