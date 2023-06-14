/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:58:04 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 21:49:09 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_heredoc(char *str)
{
	char	*buf;

	while (1)
	{
		buf = readline(">");
		if (!buf)
			break ;
		if (ft_strcmps(buf, str))
			break ;
	}
}

int	take_token(t_token *token, t_lexim *lexim)
{
	if (!*token && (lexim->token == PIPE || lexim->token == RDIRIN
			|| lexim->token == RDIROUT || lexim->token == HERE_DOC
			|| lexim->token == APPEND))
	{
		*token = lexim->token;
		if (lexim->content && ft_strlen(lexim->content) > 2)
		{
			ft_fdprintf(2,
				"minishell: syntax error near unexpected token`%c'\n", *token);
			return (1);
		}
		if (*token == PIPE)
		{
			if (ft_strlen(lexim->content) > 1)
			{
				ft_fdprintf(2,
					"minishell: syntax error near unexpected token`%c'\n",
					*token);
				return (1);
			}
			if (lexim->next)
				*token = 0;
		}
	}
	return (0);
}

static int	syntax_error_msg(t_lexim *lexim)
{
	if (lexim->next && (lexim->next->token == PIPE
			|| lexim->next->token == RDIRIN
			|| lexim->next->token == RDIROUT
			|| lexim->next->token == HERE_DOC
			|| lexim->next->token == APPEND))
	{
		ft_fdprintf(2,
			"minishell: syntax error near unexpected token `%c'\n",
			lexim->next->token);
		g_grl->exit_status = 258;
		return (1);
	}
	return (0);
}

static void	print_error(void)
{
	ft_fdprintf(2,
		"minishell: syntax error near unexpected token `newline'\n");
	g_grl->exit_status = 258;
}

int	check_token_syntax(t_lexim *lexim)
{
	t_token	token;

	token = 0;
	while (lexim)
	{
		if (lexim && (lexim->token == WORD || lexim->token == ENV))
			token = 0;
		if (take_token(&token, lexim))
		{
			g_grl->exit_status = 258;
			return (1);
		}
		if (token)
		{
			if (syntax_error_msg(lexim))
				return (1);
		}
		if (!lexim->next && token)
		{
			print_error();
			return (1);
		}
		lexim = lexim->next;
	}
	return (0);
}
