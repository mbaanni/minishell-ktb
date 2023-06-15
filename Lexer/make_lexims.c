/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lexims.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:49:53 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 12:56:36 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*sub_spe_lexim(char *str)
{
	int		i;
	char	*lexim;
	int		j;

	j = 0;
	i = 0;
	if (str[i] == '"' || str[i] == '\'')
		i = count_chars_for_quotes(&str[i]);
	else if (str[i] == '$' && str[i + 1] != '$')
		i = count_chars_for_env(&str[i]);
	else
		i = count_chars_for_rep(&str[i]);
	lexim = my_alloc(i + 1);
	if (!lexim)
		return (0);
	j = 0;
	while (str[j] && j < i)
	{
		lexim[j] = str[j];
		j++;
	}
	lexim[j] = '\0';
	return (lexim);
}

char	*sub_lexim(char *str)
{
	int		i;
	char	*lexim;

	i = 0;
	while (str[i] && !ft_strchr("\"'$ <>|", str[i]))
		i++;
	lexim = my_alloc(i + 1);
	if (!lexim)
		return (0);
	i = 0;
	while (str[i] && !ft_strchr("\"'$ <>|", str[i]))
	{
		lexim[i] = str[i];
		i++;
	}
	lexim[i] = '\0';
	return (lexim);
}

int	special_lexims(char *str, int i, char c, t_lexim **lexims)
{
	t_lexim	*tmp;
	int		j;

	j = 0;
	add_back(lexims, new_lexim(sub_spe_lexim(&str[i])));
	tmp = *lexims;
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->content[j])
		j++;
	(void)c;
	i += j;
	return (i);
}

t_lexim	*convert_to_lexims(char *str, int i, t_lexim *lexims)
{
	while (str[i])
	{
		if (str[i] && ft_strchr("\"'$<>|", str[i]))
			i = special_lexims(str, i, '\0', &lexims);
		else
		{
			if (str[i])
			{
				add_back(&lexims, new_lexim(sub_lexim(&str[i])));
				while (str[i] && (!ft_strchr("\"'$<>|", str[i])
						&& str[i] != ' '))
					i++;
			}
		}
		if (str[i] && str[i] == ' ')
		{
			add_back(&lexims, new_lexim(ft_strdup(" ")));
			while (str[i] && str[i] == ' ')
				i++;
		}
	}
	tokenize_elements(lexims);
	return (lexims);
}
