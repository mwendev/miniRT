/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:19:20 by mwen              #+#    #+#             */
/*   Updated: 2022/03/16 20:10:54 by mwen             ###   ########.fr       */
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
	mlx_string_put(m, w, 15, y += 20, 65280, "You can:");
	mlx_string_put(m, w, 15, y += 25, 65280, "Currently selected:");
	mlx_string_put(m, w, 30, y += 25, 65280, put_selected(data));
	if (data->selected.shape == 'l' || data->selected.shape == 's'
		|| data->selected.shape == 'y' || data->selected.shape == 'o')
		mlx_string_put(m, w, 38, y += 25, 65280, num);
	free(num);
}

void	put_pixel(t_data *data, int *i)
{
	char	*dst;
	int		menu_wid;

	menu_wid = WIDTH / 4;
	dst = data->img_addr + i[0] * data->line_len + i[1] * data->bits_per_pixel / 8;
	// if (i[1] < menu_wid)
	// 	*(unsigned int *) dst = 0x000000;
	// else if (i[1] < WIDTH && i[0] < HEIGHT)
		*(unsigned int *) dst = data->curr_col;
}
