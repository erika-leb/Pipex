/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_part3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:10:46 by ele-borg          #+#    #+#             */
/*   Updated: 2024/10/24 21:18:43 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		size1;
	int		size2;
	int		j;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (size1 + size2 + 1));
	i = 0;
	j = 0;
	if (str == 0)
		return (NULL);
	while (i < size1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < size1 + size2)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

void	ft_free_int(int **str, int nb)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (i < nb)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (!(*tab))
		return ;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

void	free_std(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}
