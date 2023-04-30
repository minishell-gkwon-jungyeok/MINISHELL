/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:48:59 by gkwon             #+#    #+#             */
/*   Updated: 2022/11/20 21:51:45 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*clear_return(t_list *head, void *new, void (*del)(void *))
{
	ft_lstclear(&head, del);
	del(new);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*new;
	t_list	*tmp;
	t_list	*head;

	if (!lst)
		return (0);
	new = f(lst->content);
	head = ft_lstnew(new);
	if (!head)
	{
		del(new);
		return (0);
	}
	lst = lst->next;
	while (lst)
	{
		new = f(lst->content);
		tmp = ft_lstnew(new);
		if (!tmp)
			return (clear_return(head, new, del));
		ft_lstadd_back(&head, tmp);
		lst = lst->next;
	}
	return (head);
}
