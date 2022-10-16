/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:42:24 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 17:29:16 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

typedef enum e_type_token{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_RED_OUT,
	TOKEN_RED_IN,
	TOKEN_RED2_OUT,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PAREN_IN,
	TOKEN_PAREN_OUT,
}	t_type_token;

typedef enum e_state{
	DEFAULT,
	DOU_QUOTHE,
	SIN_QUOTHE,
	PARENT,
}		t_state;

typedef struct s_token
{
	t_type_token	type;
	char			*here_doc;
	t_state			state;
	char			*cmd;
	int				index;
	int				len;
	int				start;
	struct s_token	*next;
	int				exp;
}	t_token;

typedef struct s_scanner{
	t_token				*curr_token;
	t_token				*next_token;
}				t_scanner;

t_state		check_state(char c);
void		alloc_token(t_token **token);
void		free_token(t_token **token);
void		scanner_token(t_token *token, t_scanner **curr_scan);
void		set_num(int *n);
int			token_and(t_token *token, char *line, int i);
int			token_red_in(t_token *token, char *line, int i);
int			token_red_out(t_token *token, char *line, int i);
int			token_pipe(t_token *token, char *line, int i);
int			is_token(char c);
int			is_redirection(t_type_token type);

#endif