/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_part1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:11:21 by ele-borg          #+#    #+#             */
/*   Updated: 2024/10/22 21:08:06 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	number_words(char *s, char c)
{
	int	i;
	int	r;

	i = 1;
	r = 0;
	if (ft_strlen(s) == 0)
		return (0);
	if (s[0] != c)
		r++;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			r++;
		i++;
	}
	return (r);
}

int	write_word_path(char **str, char *s, int t, int nb)
{
	int	k;

	k = 0;
	str[nb] = malloc(sizeof(char) * (t + 2));
	if (str[nb] == 0)
	{
		ft_free(str, nb);
		return (1);
	}
	while (k < t)
	{
		str[nb][k] = s[k];
		k++;
	}
	str[nb][k] = '/';
	str[nb][k + 1] = '\0';
	return (0);
}

char	**ft_split_path(char *s, char c)
{
	char	**str;
	char	*s1;
	int		nb;
	int		t;

	nb = number_words(s, c);
	str = malloc(sizeof(char *) * (nb + 1));
	if (str == 0)
		return (NULL);
	nb = 0;
	s1 = (char *) s;
	while (*s1)
	{
		t = 0;
		if ((s1 == s && s[0] != c) || (*s1 != c && *(s1 - 1) == c))
		{
			while (*(s1 + t) && *(s1 + t) != c)
				t++;
			if (write_word_path(str, s1, t, nb++) == 1)
				return (NULL);
		}
		s1++;
	}
	str[nb] = NULL;
	return (str);
}

int	write_word_cmd(char **str, char *s, int t, int nb)
{
	int	k;

	k = 0;
	str[nb] = malloc(sizeof(char) * (t + 1));
	if (str[nb] == 0)
	{
		ft_free(str, nb);
		return (1);
	}
	while (k < t)
	{
		str[nb][k] = s[k];
		k++;
	}
	str[nb][k] = '\0';
	return (0);
}

char	**ft_split_cmd(char *s, char c)
{
	char	**str;
	char	*s1;
	int		nb;
	int		t;

	nb = number_words(s, c);
	str = malloc(sizeof(char *) * (nb + 1));
	if (str == 0)
		return (NULL);
	nb = 0;
	s1 = (char *) s;
	while (*s1)
	{
		t = 0;
		if ((s1 == s && s[0] != c) || (*s1 != c && *(s1 - 1) == c))
		{
			while (*(s1 + t) && *(s1 + t) != c)
				t++;
			if (write_word_cmd(str, s1, t, nb++) == 1)
				return (NULL);
		}
		s1++;
	}
	str[nb] = NULL;
	return (str);
}
