/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:20:51 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/08 11:12:14 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	unset_env(t_env *envp, char *cmd)
{
	t_env	*tmp;

	tmp = envp;
	while (envp)
	{
		if (!ft_strncmp(envp->id, cmd, -1))
		{
			if (tmp == envp)
				general->env_head = general->env_head->next;
			else
				tmp->next = envp->next;
		}
		tmp = envp;
		envp = envp->next;
	}
}

void	ft_unset(t_command *cmd)
{
	int		i;
	t_env	*envp;

	i = 0;
	while (cmd->command_args[++i])
	{
		envp = general->env_head;
		if (!(ft_isalpha(cmd->command_args[i][0])
				|| cmd->command_args[i][0] == '_')
			|| find_char(cmd->command_args[i], '='))
			ft_fdprintf(2, "Minishell: unset: `%s': not a valid identifier\n",
					cmd->command_args[i]);
		else
			unset_env(envp, cmd->command_args[i]);
	}
	general->exit_status = 0;
}
