/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:12:45 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/01 16:24:50 by aaggoujj         ###   ########.fr       */
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
	DOU_QUOTHE,
	SIN_QUOTHE,
	PARENT,
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
	t_token				*token;
	t_scanner			*scanner;
	t_ast				*ast;
	t_ast				*root;
	t_state				state;
	int					len;
	int					dou_quothe;
	int					sin_quothe;
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
char		*ft_alloc_cmd(char *str, char *str2);
char		**alloc_tab(t_data *data, t_type_token type);
void		append_char(char **line, char c);
void		free_token(t_token **token);
void		scanner_token(t_token *token, t_scanner **curr_scan);

//****************************************************************
void		sigint_handler(int sig);
void		_ctrl_handler(void);
void		ctrl_d_handler(t_data *data);
void		tokenizetion(t_token **token, char *line, t_data *data);
int			ft_exit_ps(char *str, char *str2);
int			is_token(char c);
t_state		check_state(char c);

int			ft_dou_quote(char *line, t_token *token, int i, t_data *data);
int			ft_sin_quote(char *line, t_token *token, int i, t_data *data);
int			add_token(char *line, t_token **token, int i, t_data *data);
void		append_char(char **line, char c);
int			ft_str_cpyn(char *line, t_token **token, int i, t_data *data);

int			check_line(t_token *token, t_data *data, char *line);
t_ast		*ft_create_ast(void);
t_ast*		parcing(t_data *data, t_ast *ast, t_scanner *scan);
t_ast		*parc_opera(t_scanner *scan, t_ast *ast, t_data *data);
t_ast		*parc_paren(t_scanner *scan, t_ast *ast, t_data *data);
t_ast		*parc_pipe(t_scanner *scan, t_data *data, t_ast *root, t_ast *ast);
t_ast		*parc_word(t_scanner *scan, t_data *data, t_ast *root);
void		free_ast(t_ast *root);
void		free_table(char **table);
t_ast		*parc_word2(t_scanner *scan, t_data *data, t_ast *root);

#endif /* MINISHELL_H */