/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:12:45 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/23 23:11:18 by aaggoujj         ###   ########.fr       */
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
# include "../lib/libft/include/libft.h"


typedef enum e_type_token{
	TOKEN_WORD,
	TOKEN_SEPARATOR,
	TOKEN_RED2_OUT,
	TOKEN_PIPE,
	TOKEN_RED_IN,
	TOKEN_RED_OUT,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
} t_type_token;
typedef struct s_token
{
	t_type_token type_token;
	char			*cmd;
	int				type;
	int				index;
	int				len;
	int				start;
	struct s_token	*next;
}		t_token;
//****************************************************************

int		token_and(t_token *token, char *line, int i);
int		token_paren(t_token *token, char *line, int i);
int		token_red_in(t_token *token, char *line, int i);
int		token_red_out(t_token *token, char *line, int i);

//****************************************************************
void	sigint_handler(int sig);
void	_ctrl_handler(void);
void	ctrl_d_handler(void);
void	tokenizetion(t_token **token, char *line);

#endif /* MINISHELL_H */