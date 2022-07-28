/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:12:45 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/28 10:41:05 by aaggoujj         ###   ########.fr       */
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
	QUOTHE,
}		t_state;

typedef struct s_token
{
	t_type_token	type;
	t_state			state;
	char			*cmd;
	int				index;
	int				len;
	int				start;
	struct s_token	*next;
}	t_token;
typedef struct s_ast{
	char			*cmd;
	char			**args;
	int				in;
	int				out;
	t_type_token	type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_scanner{
	t_token				*curr_token;
	t_token				*next_token;
}					t_scanner;

typedef struct t_data{
	char				*line;
	t_token				*token;
	t_scanner			*scanner;
	t_ast				*ast;
	t_ast				*root;
	int					len;
	int					quothe;
	int					parenthes;
	int					operator;
}		t_data;


//****************************************************************

int			token_and(t_token *token, char *line, int i);
int			token_paren(t_token *token, char *line, int i, t_data *data);
int			token_red_in(t_token *token, char *line, int i);
int			token_red_out(t_token *token, char *line, int i);
int			token_pipe(t_token *token, char *line, int i);
void		*ft_any_alloc(size_t size, size_t len);
void		alloc_token(t_token **token);
void		append_char(char **line, char c);
void		free_token(t_token **token);
void		scanner_token(t_token *token, t_scanner **curr_scan);

//****************************************************************
void		sigint_handler(int sig);
void		_ctrl_handler(void);
void		ctrl_d_handler(void);
void		tokenizetion(t_token **token, char *line, t_data *data);

int			is_token(char c);
t_state		check_state(char c);

int			ft_quote(char *line, t_token *token, int i, t_data *data);
int			add_token(char *line, t_token **token, int i, t_data *data);
void		append_char(char **line, char c);
int			ft_str_cpyn(char *line, t_token **token, int i, t_data *data);

int			check_line(t_token *token, t_data *data, char *line);
void		parcing(t_data *data);

#endif /* MINISHELL_H */