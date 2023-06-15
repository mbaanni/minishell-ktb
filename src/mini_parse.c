/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:53:49 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/15 15:48:37 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

char	*ft_trime_side(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	new = 0;
	j = ft_strlen(str);
	while (str[i] && (str[i] == '\t' || str[i] == ' '))
		i++;
	while (j > 0 && (str[j - 1] == '\t' || str[j - 1] == ' '))
		j--;
	new = ft_substr(str, i, j - i);
	ft_myalloc_dell(str);
	return (new);
}

char	*get_path(char *argu)
{
	char	*path_full;
	char	**split_path;
	char	*bin;
	int		i;

	i = 0;
	if (!argu)
		return (argu);
	if (!access(argu, X_OK))
		return (argu);
	path_full = ft_getenv("PATH");
	if (!path_full)
		return (argu);
	split_path = ft_split(path_full, ':');
	while (split_path && split_path[i])
	{
		bin = ft_strjoin(split_path[i], "/");
		bin = ft_strjoin(bin, argu);
		if (access(bin, F_OK) == 0)
			return (bin);
		ft_myalloc_dell(bin);
		i++;
	}
	return (argu);
}

void	find_path(void)
{
	t_command	*ptr;
	int			i;

	i = 0;
	ptr = g_grl->command_head;
	while (ptr)
	{
		if (!ptr->command_args)
			return ;
		if (check_for_built_in(ptr, 0) || *ptr->command_args[0] == 0)
			ptr->command_path = ft_strdup(*ptr->command_args);
		else
			ptr->command_path = get_path(*ptr->command_args);
		ptr = ptr->next;
	}
}
