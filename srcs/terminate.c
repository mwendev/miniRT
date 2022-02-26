/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:41:02 by mwen              #+#    #+#             */
/*   Updated: 2022/02/25 20:36:18 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	terminate(t_data *data, char *msg, int if_exit)
{
	/*freeing t_window will be implemented later*/
	if (msg)
		perror(msg);
	if (if_exit)
		exit (if_exit);
	return (1);
}
