/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:01:09 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/05/26 18:44:15 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** *lst == begin == *t_list
** 1. begin == NULL: new.next points to NULL and begin becomes new (first elem)
** 2. &begin points to first elem: new.next points to first elem (because it
** points to where &begin points), and begin becomes new. 
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new -> next = *lst;
		*lst = new;
	}
}
