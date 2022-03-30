/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:11:51 by mwen              #+#    #+#             */
/*   Updated: 2022/03/17 20:45:37 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cy(char *str, t_data *data, int type, t_cylinder *new)
{
	int	i;

	i = 0;
	if (!new)
		return (terminate(data, "Error\nMalloc for cylinder failed", 1));
	new->prev = NULL;
	new->next = NULL;
	if (!data->cylinders)
		data->cylinders = new;
	else
	{
		data->cylinders->next = new;
		new->prev = data->cylinders;
		data->cylinders = data->cylinders->next;
	}
	while (str[i] != '\n' && str[i++])
		if (str[i] != ' ' && str[i] != '\t' && ++type)
			if ((type == 1 && parse_farray(parse_info(str, &i), new->coord, 0))
				|| (type == 2 && parse_farray(parse_info(str, &i), new->orient,
						1)) || (type == 3 && stof(parse_info(str, &i),
						&new->diameter, 1)) || (type == 4 && stof(parse_info
						(str, &i), &new->height, 1)) || (type == 5
					&& parse_color(parse_info(str, &i), new->rgb)))
				return (terminate(data, NULL, 0));
	if (type > 5 || new->diameter <= 0 || new->height <= 0)
		return (terminate(data, "Error\nInvalid params to cylinder", 0));
	return (0);
}

int	parse_pl(char *str, t_data *data, int type, t_plane *new)
{
	int	i;

	i = 0;
	if (!new)
		return (terminate(data, "Error\nMalloc for sphere failed", 1));
	new->prev = NULL;
	new->next = NULL;
	if (!data->planes)
		data->planes = new;
	else
	{
		data->planes->next = new;
		new->prev = data->planes;
		data->planes = data->planes->next;
	}
	while (str[i] != '\n' && str[i++])
		if (str[i] != ' ' && str[i] != '\t' && ++type)
			if ((type == 1 && parse_farray(parse_info(str, &i), new->coord, 0))
				|| (type == 2 && parse_farray(parse_info(str, &i),
						new->orient, 1)) || (type == 3 && parse_color
					(parse_info(str, &i), new->rgb)))
				return (terminate(data, NULL, 0));
	if (type > 3)
		return (terminate(data, "Error\nInvalid params to plane", 0));
	return (0);
}

int	parse_sp(char *str, t_data *data, int type, t_sphere *new)
{
	int	i;

	i = 0;
	if (!new)
		return (terminate(data, "Error\nMalloc for sphere failed", 1));
	new->prev = NULL;
	new->next = NULL;
	if (!data->spheres)
		data->spheres = new;
	else
	{
		data->spheres->next = new;
		new->prev = data->spheres;
		data->spheres = data->spheres->next;
	}
	while (str[i] != '\n' && str[i++])
		if (str[i] != ' ' && str[i] != '\t' && ++type)
			if ((type == 1 && parse_farray(parse_info(str, &i), new->coord, 0))
				|| (type == 2 && stof(parse_info(str, &i), &new->diameter, 1))
				|| (type == 3 && parse_color(parse_info(str, &i), new->rgb)))
				return (terminate(data, NULL, 0));
	if (type > 3 || new->diameter <= 0)
		return (terminate(data, "Error\nInvalid params to sphere", 0));
	return (0);
}

int	parse_light(char *str, t_data *data, int type, t_light *new)
{
	int	i;

	i = 0;
	if (!new)
		return (terminate(data, "Error\nMalloc for light failed", 1));
	new->prev = NULL;
	new->next = NULL;
	if (!data->lights)
		data->lights = new;
	else
	{
		data->lights->next = new;
		new->prev = data->lights;
		data->lights = data->lights->next;
	}
	while (str[i] != '\n' && str[i++])
		if (str[i] != ' ' && str[i] != '\t' && ++type)
			if ((type == 1 && parse_farray(parse_info(str, &i), new->coord, 0))
				|| (type == 2 && stof(parse_info(str, &i), &new->ratio, 1))
				|| (type == 3 && parse_color(parse_info(str, &i), new->rgb)))
				return (terminate(data, NULL, 0));
	if (type > 3 || new->ratio < 0 || new->ratio > 1.0)
		return (terminate(data, "Error\nInvalid params to light", 0));
	return (0);
}
