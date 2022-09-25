/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_fon.cc                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:40:54 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/24 20:41:29 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_here_doc(t_token **token, t_data *data)
{
	(*token)->type = TOKEN_HEREDOC;
	data->here_doc = 1;
}