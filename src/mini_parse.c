/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:53:49 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/08 12:11:10 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

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
		i++;
	}
	return (argu);
}

void	find_path(void)
{
	t_command	*ptr;
	int			i;

	i = 0;
	ptr = general->command_head;
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
