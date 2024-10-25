/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:42:58 by ele-borg          #+#    #+#             */
/*   Updated: 2024/10/21 13:26:15 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(t_pipe *var, int ac, t_node	*arg)
{
	int	i;
	int	t;

	i = 0;
	while (i < ac - 4)
	{
		t = pipe(var->pipes[i]);
		if (t == -1)
		{
			free_var(var, ac);
			ft_lstclear(arg);
			perror("pipe creation");
			exit(1);
		}
		i++;
	}
}

void	close_pipes(t_pipe *var, int ac)
{
	int	k;

	k = 0;
	while (k < ac - 4)
	{
		close(var->pipes[k][1]);
		close(var->pipes[k][0]);
		k++;
	}
}

void	part_close(t_pipe *var, int k)
{
	while (k < var->ac - 4)
	{
		close(var->pipes[k][1]);
		close(var->pipes[k][0]);
		k++;
	}
}

void	wait_for_children(t_pipe *var)
{
	int	i;

	i = 0;
	while (i < var->nmb_chdrn)
	{
		wait(NULL);
		i++;
	}
}
