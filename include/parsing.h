/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:44:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/05 17:58:06 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "data.h"

typedef struct s_ast{
	char			*cmd;
	char			**args;
	char			**args_exp;
	int				in;
	int				out;
	int				exp;
	t_type_token	type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*here_doc;
}	t_ast;

void		parc_red_in2(t_ast *root, t_ast *ast, t_ast *new);
t_ast		*last_ast(t_ast *ast);
t_ast		*copy_ast(t_ast *ast);
t_ast		*ft_create_ast(void);
void		free_ast(t_ast *root);
void		ast_add_left(t_ast **ast, t_ast *new);
void		ast_add_right(t_ast **ast, t_ast *new);

#endif