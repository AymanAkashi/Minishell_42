/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:44:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/19 18:33:17 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "tokenization.h"
#include "data.h"


typedef struct s_ast{
	char			*cmd;
	char			**args;
	int				in;
	int				out;
	t_type_token	type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*here_doc;
}	t_ast;


t_ast		*ft_create_ast(void);
void		free_ast(t_ast *root);
void		ast_add_left(t_ast **ast, t_ast *new);
void		ast_add_right(t_ast **ast, t_ast *new);

#endif