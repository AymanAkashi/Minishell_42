/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:16:13 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/03 11:19:02 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->in != STDIN_FILENO)
		close(ast->in);
	if (ast->out != STDOUT_FILENO)
		close(ast->out);
	if (ast->left)
		close_all(ast->left);
	if (ast->right)
		close_all(ast->right);
}
