/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:45:30 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 18:34:32 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_data(t_env	*ptr)
{
	int		i;

	i = -1;
	ft_fdprintf(1, "=\"");
	while (ptr->data[++i])
	{
		if (ptr->data[i] == '"' || ptr->data[i] == '$')
			ft_fdprintf(1, "\\");
		ft_fdprintf(1, "%c", ptr->data[i]);
	}
	ft_fdprintf(1, "\"");
}

int	check_argument_export(t_command *cmd)
{
	t_env	*ptr;

	ptr = g_grl->env_head;
	if (!cmd->command_args[1])
	{
		while (ptr)
		{
			if (ptr->id)
				ft_fdprintf(1, "declare -x %s", ptr->id);
			if (ptr->data)
				print_data(ptr);
			ft_fdprintf(1, "\n");
			ptr = ptr->next;
		}
		return (1);
	}
	return (0);
}

int	check_if_exicts(char *str)
{
	t_env	*ptr;
	int		len;
	int		str_len;

	ptr = g_grl->env_head;
	str_len = ft_strlen(str);
	len = index_signe(str);
	while (ptr)
	{
		if (!ft_strncmp(ptr->id, str, len))
		{
			if (ft_strlen(ptr->id) == len)
			{
				if (str_len == len)
					return (1);
				else if (len == ft_strlen(ptr->id))
				{
					ptr->data = ft_strchr_data(str);
					return (1);
				}
			}
		}
		ptr = ptr->next;
	}
	return (0);
}

int	check_identifier(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	ft_export(t_command *cmd)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	g_grl->exit_status = 0;
	if (check_argument_export(cmd))
		return ;
	while (cmd->command_args[++i])
	{
		if (check_identifier(cmd->command_args[i]))
		{
			ft_fdprintf(2, "minishell: not a valid identifier\n");
			g_grl->exit_status = 1;
		}
		else if (!check_if_exicts(cmd->command_args[i]))
			add_new_env(i, cmd->command_args);
	}
}
