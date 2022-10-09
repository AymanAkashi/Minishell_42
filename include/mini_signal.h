/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:17:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/01 19:41:47 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

# include "minishell.h"

void			sighere_handler(int sig);
void			_hidectrl(void);
void			_restctrl(void);
void			sigint_handler(int sig);
void			_ctrl_handler(void);
void			ctrl_d_handler(t_data *data);

#endif