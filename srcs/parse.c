/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:46:45 by mwen              #+#    #+#             */
/*   Updated: 2022/04/15 16:06:41 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rewind_link(t_data *data)
{
	if (data->lights)
		while (data->lights->prev)
			data->lights = data->lights->prev;
	if (data->planes)
		while (data->planes->prev)
			data->planes = data->planes->prev;
	if (data->spheres)
		while (data->spheres->prev)
			data->spheres = data->spheres->prev;
	if (data->cylinders)
		while (data->cylinders->prev)
			data->cylinders = data->cylinders->prev;
	return (0);
}

int	parse_camera(char *tr, t_data *data, int type)
{
	int	i;

	i = 0;
	while (tr[i] != '\n' && tr[i++])
	{
		if (tr[i] != ' ' && tr[i] != '\t' && ++type)
		{
			if ((type == 1 && parse_farray(parse_info(tr, &i),
						data->camera.coord, 0)) || (type == 2 && parse_farray
					(parse_info(tr, &i), data->camera.orient, 1)))
				return (1);
			if (type == 3)
				data->camera.fov = ft_atoi(tr + i);
			while (tr[i] != ' ' && tr[i] != '\t' && tr[i] != '\0')
				i++;
		}
	}
	if (type > 3)
		return (terminate(NULL, "Error\nToo many params to camera", 0));
	if (data->camera.fov < 0 || data->camera.fov > 180)
		return (terminate(NULL, "Error\nInvalid camera FOV", 0));
	return (0);
}

int	parse_ambient_light(char *tr, t_data *data)
{
	int	i;

	i = 0;
	while (tr[i] == ' ' || tr[i] == '\t')
		i++;
	if (stof(parse_info(tr, &i), &data->ambient.ratio, 1))
		return (1);
	while (tr[i] == ' ' || tr[i] == '\t')
		i++;
	if (parse_color(parse_info(tr, &i), data->ambient.rgb))
		return (1);
	while (tr[i] == ' ' || tr[i] == '\t')
		i++;
	if (tr[i] && tr[i] != '\n')
		return (terminate(NULL,
				"Error\nToo many params to ambient light", 0));
	if (data->ambient.ratio < 0 || data->ambient.ratio > 1.0)
		return (terminate(NULL, "Error\nInvalid ambient light ratio", 0));
	return (0);
}

int	parse_type(int *check, char *tr, t_data *data)
{
	int	id_len;

	id_len = 0;
	while (tr[id_len] && tr[id_len] != ' ' && tr[id_len] != '\t')
		id_len++;
	if (id_len == 1 && tr[0] == 'A' && ++(*check))
		return (parse_ambient_light(tr + id_len, data));
	else if (id_len == 1 && tr[0] == 'C' && ++(*check))
		return (parse_camera(tr + id_len, data, 0));
	else if (id_len == 1 && tr[0] == 'L' && ++(*check))
		return (parse_light(tr + id_len, data, 0, malloc(sizeof(t_light))));
	else if (id_len == 2 && !ft_strncmp(tr, "sp", 2))
		return (parse_sp(tr + id_len, data, 0, malloc(sizeof(t_sphere))));
	else if (id_len == 2 && !ft_strncmp(tr, "pl", 2))
		return (parse_pl(tr + id_len, data, 0, malloc(sizeof(t_plane))));
	else if (id_len == 2 && !ft_strncmp(tr, "cy", 2))
		return (parse_cy(tr + id_len, data, 0, malloc(sizeof(t_cylinder))));
	else if (!id_len || (id_len == 1 && *tr == '\n'))
		return (0);
	else
		return (terminate(data, "Invalid type of element in .rt", 0));
}

int	parse(int *check, char *file, t_data *data)
{
	int		fd;
	char	*tr;

	if (ft_strlen(file) == 3
		|| ft_strncmp(file + (ft_strlen(file) - 3), ".rt", 3))
		return (terminate(NULL, "Invalid file extension", 1));
	fd = open(file, O_RDONLY);
	if (fd)
	{
		while (get_next_line(fd, &tr) >= 0 && *tr)
		{
			if (parse_type(check, tr, data))
			{
				free(tr);
				exit (close(fd));
			}
			free(tr);
		}
		free(tr);
		close(fd);
		return (rewind_link(data));
	}
	return (terminate(NULL, "Open file failed", 1));
}
