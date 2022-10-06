/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:12:45 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/06 15:21:36 by aaggoujj         ###   ########.fr       */
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
# include "data.h"
# include "parsing.h"
# include "mini_signal.h"
# define NO_SUCH_DIR "minishell: cd: no such file or directory:"
# define ERROR_CD "cd: error retrieving current directory: getcwd: "
# define ERROR_CD2 "cannot access parent directories: No such file or director"
# define ECHECK "minishell: syntax error near unexpected token `"
//****************************************************************

int	g_exitstatus;

typedef struct s_env
{
	char	*name;
	char	*value;
	int		print;
}				t_env;

typedef struct s_wild
{
	char			**args;
	char			**src;
	DIR				*dir;
	struct dirent	*wild;
}		t_wild;

int			check_wildcard(char *str);
int			size_dir(DIR *dir);
char		**wildcard_str(char **str, char *src);
char		*ft_join_sep(char *s1, char *s2, char sep);
void		free_signal(t_data *data);
void		alloc_empty_envp(t_data *data);
void		parcing_word_red(t_scanner *scan, t_data *data, t_ast *new);
char		**d_alloc_tabs(char **args, char *str);
void		close_all(t_ast *ast);
void		write_heredoc(int p, char *line);
char		*read_heredoc(int p, int len, int *byte);

char		*get_thecmd(char **path, char *cmd);
int			check_cmd(char *str, t_data *data);
int			is_builting(char *str);
void		exec_builting(char *str, t_data *data, char **args);
t_ast		*just_red(t_scanner *scan, t_data *data);
t_ast		*parc_red_in(t_scanner *scan, t_ast *root,
				t_ast *ast, t_data *data);
t_ast		*parc_red_here(t_scanner *scan, t_ast *root,
				t_ast *ast, t_data *data);
t_ast		*parc_red_out(t_scanner *scan, t_ast *root,
				t_ast *ast, t_data *data);

void		__reset_sig(int def);
void		ft_dup(int in, int out, int p);
int			step_exec_cmd(t_ast *ast, t_data *data, int *absolut);

void		execut_red_out(t_ast *ast, t_ast *red);
void		execut_red_out2(t_ast *ast, t_ast *red);
void		execut_red_in(t_ast *ast, t_ast *red);
void		execut_heredoc(t_ast *ast, t_ast *red, t_data *data, int *pip);
int			check_cmd(char *str, t_data *data);
void		child_cmd(t_ast *ast, t_data *data, int absolut, char *str);
int			execut_redirection(t_ast *ast, t_ast *red, t_data *data);
int			is_builting(char *str);
void		exec_builting(char *str, t_data *data, char **args);
int			exec_red(t_ast *ast, t_data *data);

int			search_quote(char *str);
void		add_redirection(t_ast *ast, t_scanner *scan, t_data *data);
int			expand_dou_quote(char *line, int i, char **result, t_data *data);
int			expand_sin_quote(char *line, int i, t_state *state, char **result);
int			add_exitstatue(char **result);
int			close_quote(char *str, char c, int index);
void		add_shlvl(t_data *data);
int			is_type_token(t_type_token type);
void		set_here_doc(t_token **token, t_data *data);
char		*expander(char *line, t_data *data);
void		free_null(void	**ptr);
void		update_underscore(t_data *data, char **args);
void		ft_exit(char **args, t_data *data);
void		ft_pwd(t_data *data);
void		ft_unset(t_data *data, char **args);
void		ft_env(t_data *data);
void		add_export_var(t_data *data, char *cmd);
void		creat_export_var(t_data *data, char *cmd);
void		print_err(char *str, char *s, int fd);
void		ft_export(t_data *data, char **cmd);
int			type_caracter(char c);
t_env		*search_env2(char *name, t_list	*lst);
int			ft_echo(char **cmd);
char		**check_args(char **args);
char		*ft_revsplit(char **str, char sep);
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
int			type_heredoc(t_token **token, t_data *data, char *eof);
t_env		*ft_env_new(char *name, char *value);
void		ft_env_del(t_env *env);
void		alloc_envp(t_data *data, char *envp[], t_list *head);
void		sort_list(t_list *lst, t_list *head);

void		beg_minishell(t_data *data);
void		free_list(t_list *lst);
void		free_ast(t_ast *root);
void		free_all(t_data *data, int pos);
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

int			ft_cd(t_data *data, char **cmd);
t_env		*ft_get_env(void *env);
int			ft_update_oldpwd(t_list *env);

#endif /* MINISHELL_H */