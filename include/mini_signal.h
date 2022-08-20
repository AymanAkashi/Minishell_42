/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashi <akashi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:17:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/19 21:11:26 by akashi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
#define MINI_SIGNAL_H

#include "minishell.h"

void		sigint_handler(int sig);
void		_ctrl_handler(void);
void		_reset_ctrl_handler(void);
void		ctrl_d_handler(t_data *data);

#endif