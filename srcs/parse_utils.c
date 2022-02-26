/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:15:55 by mwen              #+#    #+#             */
/*   Updated: 2022/02/26 02:22:59 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

unsigned long	ft_itohexa(int *rgb)
{
	return (((rgb[0] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + (rgb[2] & 0xff));
}

int	ft_atof(char *line, float *f, int if_free)
{
	int		i;
	int		fact;
	float	sub_zero;

	i = 0;
	fact = 1;
	sub_zero = 0.1;
	if (!line)
		return (1);
	if (line[i] == '-' && ++i)
		fact = -1;
	*f = ft_atoi(line) * fact;
	while (line[i++] && line[i] != '.')
		continue ;
	while (line[i++] && line[i] >= '0' && line[i] <= '9')
	{
		*f += (line[i] - '0') * sub_zero;
		sub_zero *= 0.1;
	}
	*f *= fact;
	if (if_free)
		free(line);
	return (0);
}

int	parse_farray(char *line, float *array, int orientation)
{
	int		i;
	int		invalid;
	char	**split;

	if (!line)
		return (1);
	i = -1;
	invalid = 0;
	split = ft_split(line, ',');
	free(line);
	while (split[++i])
	{
		if (i < 3 && !ft_atof(split[i], &array[i], 0))
			if (orientation && (array[i] > 1.0 || array[i] < -1.0))
				invalid = 1;
		free(split[i]);
	}
	free(split);
	if (orientation && (i != 3 || invalid || sqrt(pow(array[0], 2)
				+ pow(array[1], 2) + pow(array[2], 2)) < 0.9))
		return (terminate(NULL, "Error\nInvalid 3d orientation value", 0));
	if (i != 3)
		return (terminate(NULL, "Error\nInvalid coordinate value", 0));
	return (0);
}

int	parse_color(char *line, int *rgb, unsigned long color)
{
	int		i;
	char	**split;

	if (!line)
		return (1);
	if (ft_strchr(line, '.') || ft_strchr(line, '-'))
	{
		free(line);
		return (terminate(NULL, "Error\nInvalid RGB value", 0));
	}
	i = -1;
	split = ft_split(line, ',');
	free(line);
	while (split[++i])
	{
		if (i < 3)
			rgb[i] = ft_atoi(split[i]);
		free(split[i]);
	}
	free(split);
	if (i != 3)
		return (terminate(NULL, "Error\nInvalid RGB value", 0));
	color = ft_itohexa(rgb);
	return (0);
}

char	*parse_information(char *line, int *i)
{
	int		len;
	int		j;
	char	*ret;

	len = 0;
	j = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && ++len)
		(*i)++;
	ret = ft_calloc(len + 1, 1);
	if (ret)
	{
		len = 0;
		while (line[j] && line[j] != ' ' && line[j] != '\t')
		{
			if (line[j] > '9' || (line[j] < '0' && line[j] != '.'
					&& line[j] != '-' && line[j] != ','))
			{
				free(ret);
				terminate(NULL, "Error:\nNon numeric in parameters", 0);
				return (NULL);
			}
			ret[len++] = line[j++];
		}
	}
	return (ret);
}
