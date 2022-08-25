/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:17:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/25 18:39:48 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
#define MINI_SIGNAL_H

#include "minishell.h"

void			_hidectrl(void);
void			_restctrl(void);
void			sigint_handler(int sig);
void			_ctrl_handler(void);
void			_reset_ctrl_handler(void);
void			ctrl_d_handler(t_data *data);

#endif