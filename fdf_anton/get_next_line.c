/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 20:35:13 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/16 21:03:58 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	analyze_buf(char **next_line, size_t buf_size, t_params *params)
{
	char	*temp_str;
	size_t	len;
	size_t	i;

	i = params->position;
	len = ft_strlen(*next_line);
	temp_str = (char *)malloc(len + buf_size + 1);
	ft_memcpy(temp_str, *next_line, len);
	free(*next_line);
	while (i < buf_size && params->buf[i] != '\n')
	{
		temp_str[len + i - params->position] = (params->buf)[i];
		i++;
	}
	temp_str[len + i - params->position] = '\0';
	len = ft_strlen(temp_str);
	*next_line = (char *)malloc(len + 1);
	ft_memcpy(*next_line, temp_str, len + 1);
	free(temp_str);
	return (i);
}

static int	end_line(t_params *params, char **line)
{
	if (params->chars == 1 && *(params->buf) == '\n')
	{
		params->position = 0;
		return (1);
	}
	if (params->chars == 0)
	{
		params->position = 0;
		return (0);
	}
	params->position = analyze_buf(line, params->chars, params);
	if (params->position == params->chars)
	{
		params->position = 0;
		return (0);
	}
	else if (params->position == params->chars - 1)
	{
		if (*(params->buf) == '\n')
		{
			params->position += 1;
			return (1);
		}
	}
	return (2);
}

static int	main_loop(t_params *params, char **line, int fd)
{
	int	el;

	el = 0;
	while (1)
	{
		if (params->chars < BUFFER_SIZE)
		{
			el = end_line(params, line);
			if (el == 1 || el == 0)
				return (el);
		}
		else
			params->position = analyze_buf(line, BUFFER_SIZE, params);
		if (params->position != BUFFER_SIZE)
		{
			params->position += 1;
			break ;
		}
		else
		{
			params->position = 0;
			params->chars = read(fd, params->buf, BUFFER_SIZE);
		}
	}
	return (2);
}

int	get_next_line(int fd, char **line)
{
	static t_params	read_params = {.chars = 0, .position = 0};
	t_params		*params;
	int				ml_return_value;

	params = &read_params;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!params->position)
		params->chars = read(fd, params->buf, BUFFER_SIZE);
	if ((int)params->chars == -1)
		return (-1);
	*line = (char *)malloc(1);
	*line[0] = '\0';
	ml_return_value = main_loop(params, line, fd);
	if (ml_return_value != 2)
		return (ml_return_value);
	return (1);
}
