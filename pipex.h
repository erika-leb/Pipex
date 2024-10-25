/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:25:42 by ele-borg          #+#    #+#             */
/*   Updated: 2024/10/25 16:45:24 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipe
{
	int		fd_in;
	int		fd_out;
	int		**pipes;
	int		*pid_tab;
	char	**env;
	int		nmb_chdrn;
	char	**mypaths;
	int		ac;
}				t_pipe;

typedef struct s_node
{
	char			**arg_and_options;
	struct s_node	*next;
}				t_node;

int		number_words(char *s, char c);
int		write_word_path(char **str, char *s, int t, int nb);
char	**ft_split_path(char *s, char c);
int		write_word_cmd(char **str, char *s, int t, int nb);
char	**ft_split_cmd(char *s, char c);

int		ft_strlen(char *str);
void	ft_free(char **str, int nb);
char	*ft_substr(char *s, int start, int len);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *s1);

char	*ft_strjoin(char *s1, char *s2);
void	ft_free_int(int **str, int nb);
void	ft_free_tab(char ***tab);
void	free_std(void);

t_node	*ft_lstnew(char **content);
void	ft_lstadd_front(t_node **lst, t_node *new);
int		ft_lstsize(t_node **lst);
t_node	*ft_lstlast(t_node *lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
void	ft_lstclear(t_node *lst);

void	free_var(t_pipe *var, int ac);
t_pipe	init_struct(int ac);
t_pipe	init(int ac, char **av, char **env);
int		**tab_pipe(int ac);
void	parsing(char **env, t_pipe *var, t_node	*arg, int ac);

t_node	*add_new(char *arg, t_pipe *var, int ac, t_node *ag);
t_node	*put_arg(int ac, char **av, t_pipe *var);
void	exit_error(t_pipe *var, t_node	*arg, int ac, char *str);

void	other_cases(int i, t_pipe *var, t_node *arg, int ac);
void	first_case(int i, t_pipe *var, t_node *arg, int ac);
void	last_case(int i, t_pipe *var, t_node *arg, int ac);
void	child_process(int i, t_pipe *var, t_node *arg, int ac);
void	create_childs(int ac, t_pipe *var, t_node *arg);

void	create_pipe(t_pipe *var, int ac, t_node	*arg);
void	close_pipes(t_pipe *var, int ac);
void	part_close(t_pipe *var, int k);
void	wait_for_children(t_pipe *var);

void	path_abs(char **cmd, t_node *arg, int i, t_pipe *var);
void	path_relat(t_pipe *var, t_node *arg, int i, char **cmd);
void	free_env(t_pipe *var, t_node *arg);
void	exec_command(int ac, t_pipe *var, t_node *arg, int i);

#endif