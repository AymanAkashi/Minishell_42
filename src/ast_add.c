/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:23:07 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/18 16:27:06 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_add_left(t_ast **ast, t_ast *new)
{
	t_ast *left;
	left = *ast;
	while(left->left)
		left = left->left;
	left->left = new;
}

void	ast_add_right(t_ast **ast, t_ast *new)
{
	t_ast *right;
	right = *ast;
	while(right->right)
		right = right->right;
	right->right = new;
}