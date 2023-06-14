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
#include "../libft/get_next_line.h"

t_general	*general;

char	*ft_trime_side(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	new = 0;
	j = ft_strlen(str);
	while (str[i] && (str[i] == '	' || str[i] == ' '))
		i++;
	while (j > 0 && (str[j - 1] == '	' || str[j - 1] == ' '))
		j--;
	new = ft_substr(str, i, j - i);
	return (new);
}

void	signal_to_take(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}

void	init_general(char **env)
{
	struct termios	terminal;

	general = my_alloc(sizeof(t_general));
	if (!general)
		exit (1);
	general->sig = 0;
	tcgetattr(0, &terminal);
	general->old_c_lflag = terminal.c_lflag;
	general->_terminal = terminal;
	general->ev = env;
	general->env_head = creat_env(env);
}

char	*readstring()
{
	char	*str;

	if (isatty(0))
	{
		str = readline("minishell> ");
		garbage_collector(str, 0);
	}
	else
		str = ft_strtrim(get_next_line(0), "\n");
	if (!str)
	{
		general->_terminal.c_lflag = general->old_c_lflag;
		tcsetattr(0, TCSANOW, &general->_terminal);
		custom_exit(general->exit_status);
	}
	return (str);
}

void	start_pr_ex(char *str)
{
	t_lexim			*lexims;
	if (str && str[0])
	{
		add_history(str);
		if (!check_syntax(str))
		{
			lexims = convert_to_lexims(str);
			if (lexims && !check_token_syntax(lexims))
			{
				find_path();
				executing_phase();
			}
		}
	}
}

int	main(int ac, char **av, char **ev)
{
	char			*str;

	(void)ac;
	(void)av;
	init_general(ev);
	signal_to_take();
	while (1)
	{
		general->_XH = -1;
		general->_terminal.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &general->_terminal);
		general->sig = 0;
		general->_XH = -1;
		str = readstring();
		str = ft_trime_side(str);
		start_pr_ex(str);
	}
	return (0);
}
