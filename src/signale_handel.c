/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signale_handel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:17:22 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/15 12:24:48 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sin_int(void)
{
	ft_fdprintf(1, "\n");
	if (g_grl->_hx != -1)
	{
		g_grl->exit_status = 1;
		close(g_grl->_hx);
		g_grl->_hx = -2;
		return (1);
	}
	else if (!g_grl->sig)
	{
		g_grl->exit_status = 1;
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	return (0);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (sin_int())
			return ;
	}
	else if (sig == SIGQUIT)
	{
		if (g_grl->sig)
			write(1, "Quit: 3\n", 8);
		rl_redisplay();
	}
	if (g_grl->sig)
	{
		g_grl->sig = 3;
		g_grl->exit_status = 128 + sig;
	}
}
