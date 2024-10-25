/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions_parta.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:32:21 by marvin            #+#    #+#             */
/*   Updated: 2024/10/17 13:07:30 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_node	*ft_lstnew(char **content)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
	{
		write(2, "Erreur memory allocation\n", 26);
		return (NULL);
	}
	new -> arg_and_options = content;
	new -> next = NULL;
	return (new);
}

void	ft_lstadd_front(t_node **lst, t_node *new)
{
	new -> next = *lst;
	*lst = new;
}

int	ft_lstsize(t_node **lst)
{
	int		s;
	t_node	*current;

	s = 0;
	current = *lst;
	if (*lst == NULL)
		return (0);
	while (current != NULL)
	{
		s++;
		current = current -> next;
	}
	return (s);
}
