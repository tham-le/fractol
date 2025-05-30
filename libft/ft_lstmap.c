/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:00:07 by thi-le            #+#    #+#             */
/*   Updated: 2022/11/17 18:00:40 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;
	t_list	*e;

	if (!lst)
		return (0);
	l = 0;
	while (lst)
	{
		e = ft_lstnew(f(lst->content));
		if (!e)
		{
			ft_lstclear(&e, del);
			return (0);
		}
		ft_lstadd_back(&l, e);
		lst = lst->next;
	}
	return (l);
}
