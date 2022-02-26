/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:49:36 by aserdyuk          #+#    #+#             */
/*   Updated: 2022/02/25 20:35:51 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		terminate(NULL, "Invalid input", 1);
	//initialize ACL
	parse(argv[1], &data);
}
