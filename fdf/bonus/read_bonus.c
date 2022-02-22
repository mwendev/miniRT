/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:36:13 by mwen              #+#    #+#             */
/*   Updated: 2021/11/22 11:54:42 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	read_size(t_fdf *data, int fd)
{
	int		i;
	char	*line;
	char	**split;

	data->map->wid = 0;
	data->map->hgt = 0;
	i = -1;
	while (get_next_line(fd, &line))
	{
		if (data->map->hgt == 0)
		{
			split = ft_split(line, ' ');
			while (split[++i])
				++data->map->wid;
			free_split(split);
		}
		++data->map->hgt;
		free(line);
	}
	free(line);
}

int	read_color(char	*hexa)
{
	int		color;
	int		i;
	char	v;

	hexa = ft_strtrim(hexa, "0x");
	i = 0;
	while (hexa[i++])
	{
		v = ((hexa[i] & 0xF) + (hexa[i] >> 6)) | ((hexa[i] >> 3) & 0x8);
		color = (color << 4) | (int)v;
	}
	free(hexa);
	return (color);
}

void	read_line(t_fdf *data, char *line, int y)
{
	int		x;
	char	**split;
	char	**color;

	data->map->p[y] = malloc((data->map->wid) * sizeof(t_point));
	if (!data->map->p[y])
		terminate(ERR_INIT_POINT, data);
	split = ft_split(line, ' ');
	x = -1;
	while (split[++x])
	{
		data->map->p[y][x].x = x;
		data->map->p[y][x].y = y;
		color = ft_split(split[x], ',');
		data->map->p[y][x].z = ft_atoi(color[0]);
		if (!color[1])
			data->map->p[y][x].color = GROUND_COL;
		else
			data->map->p[y][x].color = read_color(color[1]);
		free_split(color);
	}
	free_split(split);
}

void	read_map(t_fdf *data, char *file_name)
{
	int		fd;
	int		i;
	char	*line;

	data->map->p = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		terminate(ERR_OFILE, data);
	read_size(data, fd);
	close(fd);
	fd = open(file_name, O_RDONLY);
	data->map->p = malloc((data->map->hgt + 1) * sizeof(t_point *));
	if (!data->map->p)
		terminate(ERR_INIT_POINT, data);
	data->map->p[data->map->hgt] = 0;
	i = -1;
	while (get_next_line(fd, &line))
	{
		read_line(data, line, ++i);
		free(line);
	}
	free(line);
	assign_color(data);
	close(fd);
}
