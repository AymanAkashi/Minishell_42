/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:12:45 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/18 16:21:59 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

//******************Headers_file******************//
# include "../lib/libft/include/libft.h"
# include "tokenization.h"
#include "data.h"
# include "parsing.h"
# include "signal.h"
//****************************************************************

//****************************************************************
char		*ft_alloc_cmd(char *str, char *str2);
void		append_char(char **line, char c);
void		*ft_any_alloc(size_t size, size_t len);
int			ft_exit_ps(char *str, char *str2);
void		append_char(char **line, char c);
void		free_table(char **table);
char		**alloc_tab(t_data *data, t_type_token type, t_scanner *scan);
//****************************************************************

#endif /* MINISHELL_H */