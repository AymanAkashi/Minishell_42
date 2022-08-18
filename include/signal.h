/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:17:43 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/18 16:20:40 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
#define SIGNAL_H

#include "minishell.h"
#include "data.h"

void		sigint_handler(int sig);
void		_ctrl_handler(void);
void		ctrl_d_handler(t_data *data);

#endif