/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:17:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/18 20:48:56 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
#define SIGNAL_H

#include "minishell.h"
#include "data.h"

void		sigint_handler(int sig);
void		_ctrl_handler(void);
void		_reset_ctrl_handler(void);
void		ctrl_d_handler(t_data *data);

#endif