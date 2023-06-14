/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:27:55 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 20:06:43 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_file(char *str)
{
	int	fd[2];

	if (pipe(fd))
		return (-1);
	if (!str)
		str = "";
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	return (fd[0]);
}

int	ft_lstrcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*find_in_envs(char *str, int len)
{
	t_env	*env;

	env = g_grl->env_head;
	while (env)
	{
		if (!ft_strncmp(env->id, str, len))
		{
			if (ft_strlen(env->id) == len)
				return (env->data);
		}
		env = env->next;
	}
	return (0);
}

int	lent_identifiers(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (i);
	i = 1;
	while (str[i] && str[i] != '=' && str[i] != ' ' && str[i] != '\t')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
		i++;
	}
	return (i);
}
