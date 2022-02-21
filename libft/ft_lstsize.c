/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:41:23 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/05/26 18:47:06 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*item;
	int		i;

	if (lst == NULL)
		return (0);
	item = lst;
	i = 1;
	while (item -> next != NULL)
	{
		item = item -> next;
		i++;
	}
	return (i);
}
