/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:39:50 by ele-borg          #+#    #+#             */
/*   Updated: 2024/10/24 17:41:19 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	other_cases(int i, t_pipe *var, t_node *arg, int ac)
{
	int	k;

	k = 0;
	while (k < ac - 4)
	{
		if (k == i)
		{
			if (dup2(var->pipes[k][1], STDOUT_FILENO) == -1)
				(part_close(var, k), exit_error(var, arg, ac, "dup2 out"));
			(close(var->pipes[k][0]), close(var->pipes[k][1]));
		}
		else if (k == i - 1)
		{
			if (dup2(var->pipes[k][0], STDIN_FILENO) == -1)
				(part_close(var, k), exit_error(var, arg, ac, "dup2 in"));
			close(var->pipes[k][1]);
			close(var->pipes[k][0]);
		}
		else
		{
			close(var->pipes[k][1]);
			close(var->pipes[k][0]);
		}
		k++;
	}
}

void	first_case(int i, t_pipe *var, t_node *arg, int ac)
{
	int	k;

	k = 0;
	if (var->fd_in == -1)
		(close_pipes(var, ac), free_var(var, ac), ft_lstclear(arg), exit(1));
	if (dup2(var->fd_in, STDIN_FILENO) == -1)
		(close_pipes(var, ac), exit_error(var, arg, ac, "dup2 in"));
	while (k < ac - 4)
	{
		if (k == i)
		{
			if (dup2(var->pipes[k][1], STDOUT_FILENO) == -1)
				(part_close(var, k), exit_error(var, arg, ac, "dup2 out"));
			close(var->pipes[k][0]);
			close(var->pipes[k][1]);
		}
		else
		{
			close(var->pipes[k][1]);
			close(var->pipes[k][0]);
		}
		k++;
	}
}

void	last_case(int i, t_pipe *var, t_node *arg, int ac)
{
	int	k;

	k = 0;
	if (var->fd_out == -1)
		(close_pipes(var, ac), free_var(var, ac), ft_lstclear(arg), exit(1));
	if (dup2(var->fd_out, STDOUT_FILENO) == -1)
		(close_pipes(var, ac), exit_error(var, arg, ac, "dup2 out"));
	while (k < ac - 4)
	{
		if (k == i - 1)
		{
			if (dup2(var->pipes[k][0], STDIN_FILENO) == -1)
				(part_close(var, k), exit_error(var, arg, ac, "dup2 in"));
			close(var->pipes[k][1]);
			close(var->pipes[k][0]);
		}
		else
		{
			close(var->pipes[k][1]);
			close(var->pipes[k][0]);
		}
		k++;
	}
}

void	child_process(int i, t_pipe *var, t_node *arg, int ac)
{
	if (i == 0)
		first_case(i, var, arg, ac);
	else if (i == ac - 4)
		last_case(i, var, arg, ac);
	else
		other_cases(i, var, arg, ac);
	if (var->fd_in != -1)
	{
		close(var->fd_in);
		var->fd_in = -1;
	}
	if (var->fd_out != -1)
	{
		close(var->fd_out);
		var->fd_out = -1;
	}
}

void	create_childs(int ac, t_pipe *var, t_node *arg)
{
	int	i;

	i = 0;
	while (i < ac - 3)
	{
		var->pid_tab[i] = fork();
		if (var->pid_tab[i] == -1)
		{
			var->nmb_chdrn = var->nmb_chdrn - 1;
			perror("error fork");
		}
		if (var->pid_tab[i] == 0)
		{
			child_process(i, var, arg, ac);
			exec_command(ac, var, arg, i);
		}
		i++;
	}
}
