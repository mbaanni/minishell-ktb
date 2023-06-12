/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:18:30 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/11 22:46:58 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*find_in_env(char *str, int len)
{
	t_env *env;

	env = general->env_head;
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

int	lent_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (i);
	i = 1;
	while (str[i] && str[i] != '='  && str[i] != ' ' && str[i] != '\t')
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

char	*expand_var(char *str)
{
	int		i;
	int		j;
	char	*exp;
	char	*tmp;
	int		state;

	state = 0;
	exp = 0;
	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '"' 
				|| (str[i] == '$' && i > 0 && str[i-1] && str[i-1] != '\'') 
				|| (i == 0 && str[i] == '$') || (str[i] && str[i + 1] && str[i] == '$' && str[i + 1 ] == '?'))	
			state = 1;
		if (state && str[i + 1] && str[i] == '$' && (str[i + 1] == '?' || ft_isalpha(str[i + 1]) || str[i + 1] == '_' || ft_isdigit(str[i + 1])))
		{
			if (str[i + 1] == '?')
			{
				j = 1;
				exp = ft_itoa(general->exit_status);
			}
			else
			{
				j = lent_identifier(str + i + 1);
				exp = find_in_env(str + i + 1, j);
			}
			tmp = ft_strdup(str);
			tmp[i] = 0;
			//will segfault if s2 in strjoin in null
			if (exp)
				tmp = ft_strjoin(tmp, exp);
			str = ft_strjoin(tmp, str + i + j + 1);
			if (!exp)
				i--;
			++i;
			while (str[i] && str[i] != '$' && str[i] != '"')
			 	 i++;
			if (str[i] == '"')
				state = 0;
			if (str[i] == '$')
				i--;
		}
	}
	return (str);
}
