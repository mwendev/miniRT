/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:46:45 by mwen              #+#    #+#             */
/*   Updated: 2022/02/26 02:36:40 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	parse_camera(char *line, t_data *data, int info_type)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '\t' && ++info_type)
		{
			if (info_type == 1 && parse_farray(parse_information(line, &i),
					data->camera.coord, 0))
				return (1);
			if (info_type == 2 && parse_farray(parse_information(line, &i),
					data->camera.orient, 1))
				return (1);
			if (info_type == 3)
				data->camera.fov = ft_atoi(line + i);
			while (line[i] != ' ' && line[i] != '\t')
				i++;
		}
	}
	if (info_type > 3)
		return (terminate(NULL, "Error\nToo many params to camera", 0));
	if (data->camera.fov < 0 || data->camera.fov > 180)
		return (terminate(NULL, "Error\nInvalid camera FOV", 0));
	return (0);
}

int	parse_ambient_light(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_atof(parse_information(line, &i), &data->ambient.ratio, 1))
		return (1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (parse_color(parse_information(line, &i),
			data->ambient.RGB, data->ambient.color))
		return (1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] && line[i] != '\n')
		return (terminate(NULL,
				"Error\nToo many params to ambient light", 0));
	if (data->ambient.ratio < 0 || data->ambient.ratio > 1.0)
		return (terminate(NULL, "Error\nInvalid ambient light ratio", 0));
	return (0);
}

int	parse_type(char *line, t_data *data)
{
	int	id_len;

	id_len = 0;
	while (line[id_len] && line[id_len] != ' ' && line[id_len] != '\t')
		id_len++;
	if (id_len == 1 && line[0] == 'A')
		return (parse_ambient_light(line + id_len, data));
	else if (id_len == 1 && line[0] == 'C')
		return (parse_camera(line + id_len, data, 0));
	else if (id_len == 1 && line[0] == 'L')
		return (printf("ok\n"));
	else if (id_len == 2 && ft_strncmp(line, "sp", 2))
		return (printf("ok\n"));
	else if (id_len == 2 && ft_strncmp(line, "pl", 2))
		return (printf("ok\n"));
	else if (id_len == 2 && ft_strncmp(line, "cy", 2))
		return (printf("ok\n"));
	else if (!id_len)
		return (0);
	else
		return (terminate(data, "Invalid content in .rt", 0));
}

int	parse(char	*file, t_data *data)
{
	int		fd;
	char	*line;

	if (ft_strlen(file) == 3
		|| ft_strncmp(file + (ft_strlen(file) - 3), ".rt", 3))
		return (terminate(NULL, "Invalid file extension", 1));
	fd = open(file, O_RDONLY);
	if (fd)
	{
		while (get_next_line(fd, &line) >= 0 && *line)
		{
			if (parse_type(line, data))
			{
				free(line);
				exit (close(fd));
			}
			free(line);
		}
		free(line);
		close(fd);
		return (0);
	}
	return (terminate(NULL, "Open file failed", 1));
}
