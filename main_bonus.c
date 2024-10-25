/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:50:16 by ele-borg          #+#    #+#             */
/*   Updated: 2024/10/24 17:02:04 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipe	var;
	t_node	*arg;

	if (ac < 5)
	{
		write(1, "at least 4 arguments needed\n", 29);
		return (0);
	}
	var = init(ac, av, env);
	arg = put_arg(ac, av, &var);
	parsing(env, &var, arg, ac);
	create_pipe(&var, ac, arg);
	create_childs(ac, &var, arg);
	close_pipes(&var, ac);
	wait_for_children(&var);
	free_var(&var, ac);
	ft_lstclear(arg);
	return (0);
}
