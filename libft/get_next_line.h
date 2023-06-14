/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:57:14 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/30 16:30:10 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_nstrchr(char *str);
char	*read_line(int fd, char *line);
char	*to_ret(char *line);
char	*to_keep(char *line);

#endif