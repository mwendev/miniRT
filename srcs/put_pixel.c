/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:19:20 by mwen              #+#    #+#             */
/*   Updated: 2022/04/10 18:58:28 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*put_selected(t_data *data)
{
	if (data->selected.shape == 'c')
		return ("camera");
	else if (data->selected.shape == 'l')
		return ("light");
	else if (data->selected.shape == 's')
		return ("sphere");
	else if (data->selected.shape == 'y')
		return ("cylinder");
	else if (data->selected.shape == 'p')
		return ("plane");
	else if (data->selected.shape == 'o')
		return ("cone");
	else
		return ("");
}

void	put_menu(t_data *data)
{
	int		y;
	void	*m;
	void	*w;
	char	*num;

	y = 0;
	m = data->mlx;
	w = data->mlx_win;
	num = ft_itoa(data->selected.number);
	mlx_string_put(m, w, 15, y += 20, 65280, "The keys to");
	mlx_string_put(m, w, 15, y += 25, 65280, "selecte an object:");
	mlx_string_put(m, w, 30, y += 25, 65280, "camera: C");
	mlx_string_put(m, w, 30, y += 25, 65280, "*light: L");
	mlx_string_put(m, w, 30, y += 25, 65280, "*spher: S");
	mlx_string_put(m, w, 30, y += 25, 65280, "*plane: P");
	mlx_string_put(m, w, 30, y += 25, 65280, "*cylinder: Y");
	// mlx_string_put(m, w, 30, y += 25, 65280, "*cone: O");
	mlx_string_put(m, w, 30, y += 25, 65280, "*press again to");
	mlx_string_put(m, w, 30, y += 15, 65280, "choose the next one");
	mlx_string_put(m, w, 15, y += 25, 65280, "currently selected:");
	mlx_string_put(m, w, 30, y += 25, 65280, put_selected(data));
	if (data->selected.shape == 'l' || data->selected.shape == 's'
		|| data->selected.shape == 'y' || data->selected.shape == 'o'
		|| data->selected.shape == 'p')
		mlx_string_put(m, w, 90, y, 65280, num);
	mlx_string_put(m, w, 15, y += 25, 65280, "translate:");
	mlx_string_put(m, w, 30, y += 25, 65280, "x-axis: 1 (main pad)/E");
	mlx_string_put(m, w, 30, y += 25, 65280, "y-axis: 3 (main pad)/Q");
	mlx_string_put(m, w, 30, y += 25, 65280, "z-axis: 2 (main pad)/W");
	mlx_string_put(m, w, 15, y += 25, 65280, "rotate:");
	mlx_string_put(m, w, 30, y += 25, 65280, "x-axis: H/M");
	mlx_string_put(m, w, 30, y += 25, 65280, "y-axis: B/K");
	mlx_string_put(m, w, 30, y += 25, 65280, "z-axis: J/N");
	free(num);
}

void	put_pixel(t_data *data, int *i)
{
	char	*dst;

	dst = data->img_addr + i[0] * data->line_len + i[1]
		* data->bits_per_pixel / 8;
	*(unsigned int *) dst = data->curr_col;
}
