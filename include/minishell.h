/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:32:03 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 19:17:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/extralibft.h"
# include "limits.h"
# include <sys/types.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <assert.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>

# define READ_END		0
# define WRITE_END		1

typedef enum e_ops
{
	O_NONE,
	O_PIPE,
	O_IRED,
	O_ARED,
	O_SEMI,
	O_ORED,
	O_HERE_DOC,
	O_SPACE,
	O_ESC,
	O_DOLLAR,
	O_DQUOTE,
	O_SQUOTE,
	O_NIL,
	O_WORD,
	F_HEREDOC,
	F_APPEND,
	F_INPUT,
	F_OUTPUT
}					t_ops;
typedef struct s_execution
{
	pid_t			pid;
	int				status;
	int				pipe_fd[2];
	int				redirect_fd[2];
	int				pin;
	int				pout;
	int				size;
	int				iter;
	int				*array_pids;
}				t_execution;

typedef struct s_env
{
	char	*cmd;
	char	*var;
	char	*value;
}				t_env;

int		g_pid;

/*
** Minishell 
*/
typedef struct s_bash
{
	t_dllnode		*tokken;
	t_dllnode		*env;
	t_dllnode		*env_useless;
	t_dllnode		*pipe_line;
	t_dllnode		*cmds_list;
	char			**env_array;
	char			**path;
	t_ops			op_error;
	int				exit_code;
	int				index;
}				t_bash;

typedef enum e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef enum e_status
{
	FAILURE = -1,
	SUCCES = 0,
	NOMEM = 1
}				t_status;

t_status	compile_line(char *line, t_bash *bash);
t_bash		*bash_init(void);

/*
**	Lexer
*/

typedef struct s_lexer
{
	char			*src;
	size_t			src_size;
	char			c;
	unsigned int	i;
}					t_lexer;

t_lexer		*lexer_init(char *line);
void		lexer_free(t_lexer **lex);
void		lexer_skip_whiteO_SPACE(t_lexer *lexer);
void		lexer_advance(t_lexer *lexer);
char		lexer_gnc(t_lexer *lexer);
void		lexer_start(t_lexer *lex, t_bash *bash);
char		*ops_to_string(t_ops op);
t_ops		lexer_which_op(t_lexer *lex);
t_ops		lexer_ischar_op(char c);
void		lex_handle_quotes(char **dstring, t_ops type, t_lexer *lex);
t_status	check_syntax(t_bash *bash);
t_status	lex_errors(t_bash *sh);
void		ft_memdel(void **ap);
char		*nulled_strdup(char	*str);
/*
** Parser
*/
typedef struct s_tokken
{
	t_ops		type;
	char		*content;
}				t_tokken;

typedef struct s_char
{
	char	*src;
	int		size;
	int		i;
	char	c;
}				t_char;

t_tokken	*tokken_init(char *content, t_ops op);
void		tokken_free(void *tok);
char		*dynamic_string(char *dest, char newchar);
void		dynamic_string2(char **dest, char newchar);
void		pipe_split(t_lexer *lex, t_bash *bash);
char		*parser_strjoin(char *s1, char *s2);
char		*wrapper_strjoin(char *line, char *line2);
char		*wrapper_strjoin2(char *line, char *line2);
void		parser_handle_quotes(char **dstring, t_ops type, t_lexer *lex);

/*
**	Parser redirection
*/
t_ops		next_expected_type(t_ops curr);
void		specify_redirection(t_dllnode *tokkens);
t_dllnode	*extract_redirections(t_dllnode *parsed);

/*
**	libft tools
*/
void		ft_memdel(void **ap);

/*
**	test
*/

void		print_tokken(void *ht);
void		print_lines(void *ht);
void		print_files(void *ht);
void		test_args(char	**arg);
void		ftprintenv(t_bash **bash);
void		sfprint(void *c);
/*
**	env
*/
void		env_get(t_bash **sh, char **env);
int			w_srchenv(void *t1, void *s2);
char		**point_to_env(t_dllnode	*env);
void		get_path(t_bash **bash);
t_env		*envsmake(char *env);
t_env		*env_new(char *key, char *value);
/*
**	EXPANDER
*/
t_bool		is_metachar(char *s, int j);
void		handle_O_DOLLAR(t_lexer *lex, t_bash *sh, char **ds);
char		*parser_expand_dollar(char **args, t_bash *sh);
void		parse_dollar(t_lexer	*lex, char **string, t_bash *sh);
void		expand_dollar(t_lexer	*lex, char **string, t_bash *sh);

/*
**	give details and struct everything
*/

typedef struct s_files
{
	t_ops		type;
	char		*value;
	char		*path;
	t_bool		isheredoc;
}				t_files;

void		files_destruct(void *files);
t_files		*files_constr(t_ops type, char *value);
typedef struct s_cmdtable
{
	char		*cmd_path;
	char		**cmd_args;
	t_dllnode	*files;
	t_bool		isbuiltin;
}				t_cmdtable;

void		iter_on_cmd(t_bash *sh, t_lexer *lex);
t_cmdtable	*cmd_list_creator(t_dllnode *listargs, t_dllnode *listfiles);
void		cmd_list_destruct(void *_cmd);

/*
**	making the comand table
*/
t_dllnode	*args_finale(char *sh, t_bash *bash);
t_dllnode	*cmd_tokken_start(t_lexer	*lex,	t_bash *bash);
t_cmdtable	*make_command(t_dllnode	*cmd, t_dllnode *args, t_dllnode *files);
/*
**	execution
*/
void		execute_on_cmd(t_bash *bash);
void		execution_start_point(t_bash	*bash);
t_bool		is_builtin_parrent(char *cmd);
t_bool		is_builtin(char *cmd);
void		wait_for_childs(t_execution *exec, t_bash *bash);
void		execution_struct_destruct(t_execution **exec);

/*
**	Redirection
*/
void		*opening_files_returnfd(t_dllnode *file, t_execution *exec);
/*
**	heredoc
*/
void		here_doc_init(t_bash *sh);
/*
**	buiLtins
*/
int			builtin_execution(char **args, char **env);
t_bool		is_builtin(char *cmd);
int			get_argc(char **argv);
int			builtin_echo(char **args, char	**env);
int			builtin_cd(char **args, char	**env);
int			builtin_pwd(char **args, char	**env);
int			builtin_export(char **args, char	**env);
int			builtin_unset(char **args, char	**env);
int			builtin_env(char **args, char	**env);
int			builtin_exit(char **args, char	**env);
void		env_free(void	*env);
t_bool		if_prefix_valid(char *cmd);
t_bool		if_var_valid(char *var);
void		copy_and_delete(char **dest, char *new_value);
t_bool		isnotquoted(char *line, int i, char q);
void		ft_real_exit(char *msg, int i);
char		*after_parser_expand(char *arg, t_bash *sh);
t_status	o_ired_checker(int prev, int next, t_bash *bash);
t_status	o_ared_checker(int prev, int next, t_bash *bash);
t_status	heredoc_checker(int prev, int next, t_bash *bash);
t_status	o_ored_checker(int prev, int next, t_bash *bash);
t_status	o_semi_checker(int prev, int next, t_bash *bash);

char		*dynamic_string(char *dest, char newchar);
char		*nulled_strdup(char	*str);
t_lexer		*lexer_init(char *line);
void		lexer_free(t_lexer **lex);
void		lexer_start_loop(char **dstring, t_lexer *lex, t_dllnode **tokken);
t_ops		lexer_which_op(t_lexer *lex);
t_ops		lexer_ischar_op(char c);
void		lexer_skip_white_spaces(t_lexer *lexer);
void		dynamic_string2(char **dest, char newchar);
t_bool		is_metachar(char *s, int j);
void		ftprintenv(t_bash **bash);
int			w_srchenv(void *t1, void *s2);
void		get_path(t_bash **bash);
void		env_get(t_bash **sh, char **env);
void		iter_on_cmd(t_bash *sh, t_lexer *lex);

void		prpar_command(t_bash *sh, char *line);
void		cmd_list_destruct(void *_cmd);
t_cmdtable	*cmd_list_creator(t_dllnode *listargs, t_dllnode *listfiles);
char		**clone_ll_char(t_dllnode *list_args);
void		after_parser_removequotes(t_dllnode *list_args, t_bash *sh);
t_dllnode	*wraper_get_redirection(t_bash *sh, char *line, char **remainline);
char		*extract_args(t_dllnodec*parsed);
char		*slashify_bkslash_line(char **argsline);

/*
** signal
*/
void		signal_handler_sigquit(int sig);
void		signal_handler_sigint(int sig);

/*
**	TRICKS
*/
t_bash		*get_bash__ptr(t_bash *bash);

/*
** forks
*/

t_bool		isadirectory(char *path);;
int			is_exist(char *path);
char		*get_path_cmd(char *str, char **path);
t_bool		isredirection(t_cmdtable	*cmd);
void		execution_error(int exit_code);

/*
** forks
*/

void		print_error(char *str, char *str2, int exit_code);
void		error_management(char *path);
void		handle_execution_builin(char **argv, char **env);
t_bool		if_spaces(char *str);
int			child_open_fd(char *path, int flags);

t_execution	*execution_struct_init(int size);
void		wrapper_exec(t_cmdtable *cmd, t_bash *bash);
void		handle_exceve(char *path, char **argv, char **env);
void		*opening_files_returnfd(t_dllnode *file, t_execution *exec);
t_bool		lets_try_expand(char *path, char **cmd);

/*
** export utills
*/
t_bool		if_var_valid(char *var);
t_bool		if_prefix_valid(char *cmd);
void		copy_and_delete(char **dest, char *new_value);
int			export_var(char *cmd, t_bash *sh);
int			loop_on_env(char **args, t_bash *bash);
void		sfprint2(void *c);
int			env_cmp(t_dllnode *a, t_dllnode *b);
void		env_free(void	*env);
void		env_swap(t_dllnode *a, t_dllnode *b);
void		sort_var(t_dllnode *node);
t_bool		if_env_exist_and_update(t_env *env_new, t_bash *bash);
int			function_a(char **string_o, char **string__p);
#endif