/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:18:12 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/08 11:33:48 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_cout(int double_cout, int signle_cout)
{
	if (double_cout % 2)
	{
		ft_fdprintf(2,
				"minishell: unexpected EOF while looking for matching\n");
		general->exit_status = 1;
		return (1);
	}
	if (signle_cout % 2)
	{
		ft_fdprintf(2,
				"minishell: unexpected EOF while looking for matching\n");
		general->exit_status = 1;
		return (1);
	}
	return (0);
}
int	check_syntax(char *str)
{
	int	i;
	int	signle_cout;
	int	double_cout;

	signle_cout = 0;
	double_cout = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == '|' && i == 0) || (i == ft_strlen(str) - 1
				&& str[i] == '|'))
		{
			ft_fdprintf(2,
					"minishell: syntax error near unexpected token `|'\n");
			general->exit_status = 258;
			return (1);
		}
		if (str[i] == '"')
			double_cout++;
		if (str[i] == '\'')
			signle_cout++;
	}
	if (error_cout(double_cout, signle_cout))
	{
		general->exit_status = 258;
		return (1);
	}
	return (0);
}
