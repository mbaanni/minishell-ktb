/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:54:15 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/07 20:07:35 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_last_env(t_env *lst)
{
	while (lst->next)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_env_add_back(t_env **head, t_env *evirement)
{
	t_env	*tmp;

	if (*head)
	{
		tmp = ft_last_env(*head);
		tmp->next = evirement;
	}
	else
		*head = evirement;
}

int	index_signe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!i)
		return (ft_strlen(str));
	return (i);
}

char	*ft_strchr_data(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (0);
	if (str[i] == '=' && !str[i + 1])
	{
		str = my_alloc(1);
		*str = 0;
		return (str);
	}
	i++;
	while (str[i + j])
		j++;
	return (ft_substr(str, i, j));
}

t_env	*creat_env(char **ev)
{
	int		i;
	t_env	*head;
	t_env	*tmp;

	i = -1;
	head = 0;
	while (ev[++i])
	{
		tmp = my_alloc(sizeof(t_env));
		tmp->id = ft_substr(ev[i], 0, index_signe(ev[i]));
		tmp->data = ft_strchr_data(ev[i]);
		tmp->i = 1;
		tmp->next = 0;
		ft_env_add_back(&head, tmp);
	}
	return (head);
}
