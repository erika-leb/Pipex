/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:31:59 by ele-borg          #+#    #+#             */
/*   Updated: 2024/10/25 16:45:15 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_env(t_pipe *var, t_node *arg)
{
	free_std();
	free_var(var, var->ac);
	ft_lstclear(arg);
	write(2, "command not found\n", 19);
	exit(1);
}

void	path_abs(char **cmd, t_node *arg, int i, t_pipe *var)
{
	int	err;

	err = 0;
	(void) i;
	if (access(cmd[0], X_OK) != 0)
	{
		free_std();
		exit_error(var, arg, var->ac, "command not found");
	}
	execve(cmd[0], cmd, var->env);
	err = errno;
	if (err == 26)
	{
		write(2, "Error : Text file busy\n", 24);
		(free_var(var, var->ac), ft_lstclear(arg), exit(1));
	}
}

void	path_relat(t_pipe *var, t_node *arg, int i, char **cmd)
{
	int		j;
	char	*filepath;

	j = 0;
	(void) i;
	filepath = NULL;
	if (!var->mypaths)
		free_env(var, arg);
	while (var->mypaths[j])
	{
		if (filepath != NULL)
			free(filepath);
		filepath = ft_strjoin(var->mypaths[j], cmd[0]);
		if (filepath == NULL)
			exit_error(var, arg, var->ac, "error strjoin");
		if (access(filepath, X_OK) == 0)
			break ;
		j++;
	}
	if (!var->mypaths[j])
	{
		(free(filepath), free_std());
		exit_error(var, arg, var->ac, "command not found");
	}
	(execve(filepath, cmd, var->env), free(filepath));
}

void	exec_command(int ac, t_pipe *var, t_node *arg, int i)
{
	t_node	*current;
	int		j;

	j = 0;
	current = arg;
	while (j++ < i && current != NULL)
		current = current->next;
	if (current->arg_and_options[0] == NULL)
	{
		write(2, "command not found\n", 19);
		(free_var(var, ac), ft_lstclear(arg), exit(1));
	}
	if (current->arg_and_options[0] && current->arg_and_options[0][0]
		&& (current->arg_and_options[0][0] == '/'
		|| current->arg_and_options[0][0] == '.'))
		path_abs(current->arg_and_options, arg, i, var);
	else
		path_relat(var, arg, i, current->arg_and_options);
	(free_var(var, ac), ft_lstclear(arg), exit(1));
}
