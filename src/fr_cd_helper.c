/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:57:27 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/09/27 18:35:45 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"

// int			ft_cd(t_data *data, char **cmd);
// void		no_dir(t_data	*data);

// static int	print_error( char *args, char *msg)
// {
// 	g_exitstatus = 1;
// 	printf("minishell : %s %s\n", args, msg);
// 	return (0);
// }

// int	go_to_path(t_data *data, char **cmd)
// {
// 	char	*path;
// 	char	*pwd;

// 	path = cmd[1];
// 	pwd = getcwd(NULL, 0);
// 	if (!ft_strcmp(path, "..") && pwd == NULL)
// 		return (go_path_helper(data, path));
// 	else if (access(path, F_OK) == -1)
// 		return (print_error("cd: no such file or directory:", path), 0);
// 	if (chdir(path) == -1)
// 		return (print_error("cd: no such file or directory:", path), 0);
// 	update_pwd(data);
// 	return (1);
// }

// int	go_path_helper(t_data *data, char *path)
// {
// 	char	*msg1;
// 	char	*msg1_2;

// 	g_exitstatus = 1;
// 	msg1 = "cd: error retrieving current directory: getcwd:";
// 	msg1_2 = " cannot access parent directories: No such file or directory\n";
// 	printf("%s %s", msg1, msg1_2);
// 	if (chdir(path) == -1)
// 		return (print_error("cd: no such file or directory:", path), 0);
// 	no_dir(data);
// 	return (0);
// }
