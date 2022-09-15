/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:12:45 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/15 22:48:42 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

//******************Headers_file******************//

# include "../lib/libft/include/libft.h"
# include "tokenization.h"
#include "data.h"
# include "parsing.h"
# include "mini_signal.h"
//****************************************************************


int	g_exitstatus;

typedef struct s_env
{
	char	*name;
	char	*value;
	int		print;
}				t_env;

char		**check_args(char **args);
char		*ft_revsplit(char **str, char *sep);
int			check_str(char *str, char *src);
int			check_wildcard(char *str);
char		**wild(char *str);
void		wait_all(pid_t pid);
void		execution(t_data *data, t_ast *root);
void		exec_block(t_ast *ast, t_data *data);
void		execut_pipe(t_ast *ast, t_data *data);
void		add_path(t_data *data);
void		update_data(t_ast *ast, t_data *data);
char		*expand_heredoc(char *str, t_data *data);
int			exporting(char **result, char *line, int pos, t_data *data);
char		*ft_strjoin2(char *str, char *buff);
void		ft_env_del(t_env *env);
void		type_heredoc(t_token **token, t_data *data);
t_env		*ft_env_new(char *name, char *value);
void		ft_env_del(t_env *env);
void		alloc_envp(t_data *data, char *envp[], t_list *head);
void		ft_export_new(t_data *data);


//****************************************************************
char		*ft_alloc_cmd(char *str, char *str2);
void		append_char(char **line, char c);
void		*ft_any_alloc(size_t size, size_t len);
int			ft_exit_ps(char *str, char *str2);
void		append_char(char **line, char c);
void		free_table(char **table);
char		**alloc_tab(t_data *data, t_type_token type, t_scanner *scan);
//****************************************************************

#endif /* MINISHELL_H */