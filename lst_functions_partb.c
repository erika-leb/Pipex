/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions_partb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:32:21 by marvin            #+#    #+#             */
/*   Updated: 2024/10/19 18:57:12 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_node	*ft_lstlast(t_node *lst)
{
	t_node	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current -> next != NULL)
		current = current -> next;
	return (current);
}

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*current;

	if (!new)
		return ;
	if (!lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current -> next != NULL)
		current = current -> next;
	current -> next = new;
}

void	ft_lstclear(t_node *lst)
{
	t_node	*current;

	if (lst == NULL)
		return ;
	current = lst;
	while (lst != NULL)
	{
		current = (lst)-> next;
		ft_free_tab(&lst->arg_and_options);
		free(lst);
		lst = current;
	}
	lst = NULL;
}
