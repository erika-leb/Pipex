/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_part1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:30:53 by ele-borg          #+#    #+#             */
/*   Updated: 2024/10/24 17:33:36 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_var(t_pipe *var, int ac)
{
	int	i;

	if (var->fd_in > -1)
	{
		close(var->fd_in);
		var->fd_in = -1;
	}
	if (var->fd_out > -1)
	{
		close(var->fd_out);
		var->fd_out = -1;
	}
	if (var->pipes != NULL)
		ft_free_int(var->pipes, ac - 4);
	if (var->pid_tab != NULL)
		free(var->pid_tab);
	i = 0;
	if (var->mypaths)
	{
		while (var->mypaths[i])
			free(var->mypaths[i++]);
		free(var->mypaths);
	}
}

t_pipe	init_struct(int ac)
{
	t_pipe	var;

	var.fd_in = -1;
	var.fd_out = -1;
	var.pipes = NULL;
	var.pid_tab = NULL;
	var.env = NULL;
	var.nmb_chdrn = 0;
	var.mypaths = NULL;
	var.ac = ac;
	return (var);
}

t_pipe	init(int ac, char **av, char **env)
{
	t_pipe	var;

	var = init_struct(ac);
	var.pipes = tab_pipe(ac);
	var.fd_in = open(av[1], O_RDONLY, 0777);
	if (var.fd_in == -1)
		perror("error infile");
	var.fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (var.fd_out == -1)
		perror("error outfile");
	var.pid_tab = malloc(sizeof(int) * (ac - 3 + 1));
	if (var.pid_tab == NULL)
	{
		perror("malloc 3");
		(free_var(&var, ac), exit(1));
	}
	var.env = env;
	var.nmb_chdrn = ac - 3;
	return (var);
}

int	**tab_pipe(int ac)
{
	int	**tab;
	int	i;

	tab = malloc((ac - 4 + 1) * sizeof(int *));
	if (tab == NULL)
	{
		perror("error malloc 1");
		exit(1);
	}
	i = 0;
	while (i < ac - 4)
	{
		tab[i] = malloc(3 * sizeof(int));
		if (tab[i] == NULL)
		{
			ft_free_int(tab, i);
			perror("error malloc 2");
			exit(1);
		}
		i++;
	}
	return (tab);
}

void	parsing(char **env, t_pipe *var, t_node	*arg, int ac)
{
	char	*path_env;
	int		i;
	int		s;

	i = 0;
	path_env = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			s = ft_strlen(env[i]);
			path_env = ft_substr(env[i], 5, s - 5);
			if (path_env == NULL)
				exit_error(var, arg, ac, "error substr");
		}
		i++;
	}
	if (path_env != NULL)
	{
		var->mypaths = ft_split_path(path_env, ':');
		if (var->mypaths == NULL)
			(free(path_env), exit_error(var, arg, ac, "error split path"));
		free(path_env);
	}
}
