/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:36:10 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 17:15:27 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*sub_keycode(char *str)
{
	int		i;
	char	*keycode;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	keycode = my_alloc(i + 1);
	if (!keycode)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		keycode[i] = str[i];
		i++;
	}
	keycode[i] = '\0';
	return (keycode);
}

void	replace_str(char *str)
{
	int	i;
	int	state;

	state = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			state = 0;
			i++;
		}
		while (str[i] && !state && str[i] != '"' && str[i] != '\'')
			i++;
		if (!state)
			i++;
		if (str[i] && str[i] != '"' && str[i] != '\'')
			state = 1;
		if (state && str[i] == ' ')
			str[i] = 1;
		if (state)
			i++;
	}
}

int	check_ambigious(char *str)
{
	char	**args;
	int		i;
	int		count;

	count = 0;
	replace_str(str);
	args = ft_split(str, 1);
	if (!args[0])
		return (0);
	i = 0;
	while (args && args[i])
	{
		if (parse_string(args[i])[0])
			count++;
		i++;
	}
	if (count > 1 || !count)
		return (0);
	return (1);
}

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	if (!i)
		return (0);
	return (1);
}

int	is_wild(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '"' || str[i] == '\'')
		return (0);
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
