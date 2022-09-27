/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:12:45 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/27 18:34:21 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <paths.h>

//******************Headers_file******************//

# include "../lib/libft/include/libft.h"
# include "tokenization.h"
#include "data.h"
# include "parsing.h"
# include "mini_signal.h"

#define ECHECK "minishell: syntax error near unexpected token `"
//****************************************************************

extern int	g_exitstatus;

typedef struct s_env
{
	char	*name;
	char	*value;
	int		print;
}				t_env;

void		add_shlvl(t_data *data);
int			is_type_token(t_type_token type);
void		set_here_doc(t_token **token, t_data *data);

void		free_null(void	**ptr);
void		update_underscore(t_data *data, char **args);
void		ft_exit(char **args);
void		ft_pwd(t_data *data);
void		ft_unset(t_data *data, char **args);
void		ft_env(t_data *data);
void		add_export_var(t_data *data, char *cmd);
void		creat_export_var(t_data *data, char *cmd);
void		print_err(char *str, char *s, int fd);
void		ft_export(t_data *data, char **cmd);
int			type_caracter(char c);
t_env		*search_env2(char *name, t_list	*lst);
int			ft_echo(char **cmd, t_data *data);
char		**check_args(char **args);
char		*ft_revsplit(char **str, char *sep);
int			check_str(char *str, char *src);
int			check_wildcard(char *str);
void		update_pwd(t_data *data);
char		**wild(char *str);
void		wait_all(pid_t pid);
void		execution(t_data *data, t_ast *root);
void		exec_block(t_ast *ast, t_data *data);
void		execut_pipe(t_ast *ast, t_data *data, int p);
void		add_path(t_data *data);
char		*expand_heredoc(char *str, t_data *data);
int			exporting(char **result, char *line, int pos, t_data *data);
char		*ft_strjoin2(char *str, char *buff);
void		ft_env_del(t_env *env);
void		type_heredoc(t_token **token, t_data *data);
t_env		*ft_env_new(char *name, char *value);
void		ft_env_del(t_env *env);
void		alloc_envp(t_data *data, char *envp[], t_list *head);
void		sort_list(t_list *lst, t_list *head);

void		beg_minishell(t_data *data);
void		free_all(t_data *data);
void		first_init(char **envp, t_data *data);
void		init_data(t_data *data, char *envp[], char *line);
//****************************************************************
char		*ft_alloc_cmd(char *str, char *str2);
void		append_char(char **line, char c);
void		*ft_any_alloc(size_t size, size_t len);
int			ft_exit_ps(char *str, char *str2);
void		append_char(char **line, char c);
void		free_table(char **table);
char		**alloc_tab(t_data *data, t_type_token type, t_scanner *scan);
//****************************************************************

int			go_to_path(t_data *data, char **cmd);
int			ft_cd(t_data *data, char **cmd);
void		no_dir(t_data	*data);
t_env		*ft_get_env(void *env);
int			ft_update_oldpwd(t_list *env);
int			go_path_helper(t_data *data, char *path);

#endif /* MINISHELL_H */