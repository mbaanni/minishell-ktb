/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:30:50 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/10 12:33:42 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include"../libft/get_next_line.h"

t_general *general;

char	*ft_trime_side(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	new = 0;
	j = ft_strlen(str);
	while (str[i] && (str[i] ==  '	' || str[i] == ' '))
		i++;
	while (j > 0 && (str[j - 1] ==  '	' || str[j - 1] == ' '))
		j--;
	new = ft_substr(str, i, j - i);
	return (new);
}

void    handle_signal(int sig)
{

	if (sig == SIGINT)
	{
		if (general->sig)
			return ;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
}

void	signal_to_take()
{
	struct sigaction	sa;
	
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}

int main(int ac,char **av,char **ev)
{
	char *str;
	t_lexim	*lexims;
	(void) ac;
	(void) av;

	signal_to_take();
	general = my_alloc(sizeof(t_general));
	if(!general)
		return 0;
	general->ev = ev;
	general->env_head = creat_env(ev);
	general->sig = 0;
	while (1)
	{
		if (isatty(0))
		{
			str = readline("minishell> ");
			garbage_collector(str, 0);
		}
		else
			str = ft_strtrim(get_next_line(0),"\n");
		if(!str)
		{
			custom_exit(general->exit_status);
		}
		str = ft_trime_side(str);
		if(str && str[0])
		{
			add_history(str);
			if (!check_syntax(str))
			{
				lexims = convert_to_lexims(str);
				if (lexims && !check_token_syntax(lexims))
				{
					find_path();
					if (!ft_getenv("PATH"))
					{
						ft_fdprintf(2, "minishell: No such file or directory\n");
						general->exit_status = 127;
					}
					else
						executing_phase();
				}
			}
		}
		general->sig = 0;
	}
	return (0);
}	
