/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signale_handel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:17:22 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/04 15:18:55 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int sin_int()
{
    write(1, "\n", 1);
	if (general->_XH != -1)
	{
		general->exit_status = 1;
		close(general->_XH);
		general->_XH = -2;
		return (1);
	}
	else if (!general->sig)
	{
		general->exit_status = 1;
		rl_on_new_line();
		//rl_replace_line("", 0);
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
		if (general->sig)
			write(1, "Quit: 3\n", 8);
		rl_redisplay();
	}
	if (general->sig)
	{
		general->sig = 3;
		general->exit_status = 128 + sig;
	}
}
