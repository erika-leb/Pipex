/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:32:19 by ele-borg          #+#    #+#             */
/*   Updated: 2024/10/22 20:53:42 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_node	*add_new(char *arg, t_pipe *var, int ac, t_node *ag)
{
	t_node	*new;
	char	**tab;

	tab = ft_split_cmd(arg, ' ');
	if (!tab)
	{
		free_var(var, ac);
		perror("malloc lst");
		ft_lstclear(ag);
		exit(1);
	}
	new = ft_lstnew(tab);
	return (new);
}

t_node	*put_arg(int ac, char **av, t_pipe *var)
{
	t_node	*arg;
	t_node	*new;
	int		i;

	i = 2;
	arg = NULL;
	while (i < ac - 1)
	{
		new = add_new(av[i], var, ac, arg);
		if (!new)
		{
			free_var(var, ac);
			ft_lstclear(arg);
			perror("malloc lst");
			exit(1);
		}
		if (!arg)
			arg = new;
		else
			ft_lstadd_back(&arg, new);
		i++;
	}
	return (arg);
}

void	exit_error(t_pipe *var, t_node	*arg, int ac, char *str)
{
	free_var(var, ac);
	ft_lstclear(arg);
	perror(str);
	exit(1);
}
