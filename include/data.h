/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:11:34 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 15:56:47 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "../lib/libft/include/libft.h"
# include "tokenization.h"
# include "parsing.h"
# include "minishell.h"

typedef struct t_data{
	t_token				*token;
	t_scanner			*scanner;
	t_list				*envp;
	t_state				state;
	t_ast				*ast;
	t_ast				*root;
	char				**env;
	int					found_env;
	char				**path;
	int					here_doc;
	int					len;
	int					check_path;
	int					dou_quothe;
	int					sin_quothe;
	int					parenthes;
	int					operator;
	int					num_heredoc;
}		t_data;

t_ast		*parc_cmd(t_scanner *scan, t_data *data);
char		*remove_quotes(char *str);
char		*search_env(char *key, t_data *data);
char		*check_expender(char *args, t_data *data);
t_ast		*ast_here_doc(t_ast *ast, t_scanner *scan, t_data *data);
void		tokenizetion(t_token **token, char *line, t_data *data);
int			token_paren(t_token *token, char *line, int i, t_data *data);
int			ft_dou_quote(char *line, t_token *token, int i, t_data *data);
int			ft_sin_quote(char *line, t_token *token, int i, t_data *data);
int			add_token(char *line, t_token **token, int i, t_data *data);
int			ft_str_cpyn(char *line, t_token **token, int i, t_data *data);
int			check_line(t_token *token, t_data *data, char *line);
t_ast		*parcing(t_data *data, t_ast *ast, t_scanner *scan);
t_ast		*parc_opera(t_scanner *scan, t_ast *ast, t_data *data);
t_ast		*parc_paren(t_scanner *scan, t_ast *ast, t_data *data);
t_ast		*parc_pipe(t_scanner *scan, t_data *data, t_ast *root, t_ast *ast);
t_ast		*parc_word(t_scanner *scan, t_data *data, t_ast *root);
t_ast		*parc_redirection(t_scanner *scan, t_ast *root, t_data *data);
t_ast		*parc_word2(t_scanner *scan, t_data *data, t_ast *root);

#endif