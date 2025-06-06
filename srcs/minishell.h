/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 23:02:49 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/16 19:24:12 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//heredoc identifiers enums
# define HEREDOC_FINISH -255
# define HEREDOC_FAIL -1
# define HEREDOC_SUCCESS -100

# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../expander/ft_expander.h"
# include "../tokenizer/tokenizer.h"

# ifndef PATH_MAX
# define PATH_MAX 4096
# endif

extern volatile sig_atomic_t    g_sig;
typedef struct s_expander
{
	size_t	j;
	size_t	i;
	size_t	i_result;
	size_t	i_size;
	size_t	count;
	size_t	k;
	size_t	i_malloc;
	char	*last_exit_code;
	char	*string;
	char	*argv;
	char	*quoted;
	char	*input;
	char	*var_name;
	char	*var_value;
	char	*result;
	char	**envment;
}			t_expand;

typedef struct s_token
{
	size_t	j;
	size_t	index;
	size_t	i;
	size_t	count;
	size_t	k;
	int		error_token;
	char	c;
	char	*input;
	char	**tokens;
}			t_tok;

typedef struct s_read
{
	int		exit_status;
	int		heredocs[256];
	char	*prompt;
	char	*line;
	char	*cwd;
	char	**enviro;
	char	**tokens;
	char	**expo;
	char	***piper;
	int		piper_len;
	t_tok	*token;
	t_expand	*pand;
}				t_read;

//Minishell
int		ft_exit_shell(t_read *line);
void	ft_get_prompt(t_read *line);
void	ft_exit_with_error(t_read *line, char *str, int err);
void	terminal_shell(t_read *line);
//expander
int	comper_expander(char c);
int string_expander(char c);
size_t	count_malloc(t_expand *pand);

char	*ft_expander(t_read *line, char *last_exit_code, char *argv);
char	*get_string_expander(t_expand *pand);

void	ft_free_expander(t_expand *pand);
void	dollar_malloc_expander(t_expand *pand);
void	dollar_fill_expander(t_expand *pand);
void	single_quoted(t_expand *pand);
void	fill_value_expander(t_expand *pand, char *value);
void	var_expander(t_expand *pand);
void	initialize_pand(t_expand *pand);
void	go_to_check_arrow(t_read *line);
void	fill_arrow(t_expand *pand);
void	count_arrow(t_expand *pand);

//tokenizer
char	**ft_tokenizer(t_read *line);
void	ft_free_tokenizer(t_tok *token);
void	greater_tokenizer(t_tok *token);
void	pipe_tokenizer(t_tok *token);
void	dollar_tokenizer(t_tok *token);
void	string_tokenizer(t_tok *token);
void	initialize_tok(t_tok *token);
int		comper(char c);

//Builtin
int		builtin_part1(t_read *line, char **cmd);
void	ft_handle_cd(t_read *line, char **cmd);
void	ft_handle_echo(char **cmd);
void	ft_handle_export(t_read *line, char **cmd);
void	ft_handle_unset(t_read *line, char **cmd);
void	ft_handle_env(t_read *line, char **cmd);
char	*ft_getenv(char **enviro, char *env);
char	**fill_env(char *str, char **old_arr);
void	*copy_without_quoted(char *str, int size, char **arr);
void	*add_quoted_for_value(char **arr, int size);
char	**fill_export(char *str, char **old_arr);
char	**rplc_env(char *fnd, char **old_arr, char *rplc);
char	**rplc_export(char *fnd, char **old_arr, char *rplc);
char	*get_key(char *str, int c);
char	*check_name_of_key(char **arr, char *fetch);

//execution
char	**redirect_stdout(char **cmd);
char	**redirect_stdin(t_read *line, char **cmd);
void	ft_errmsg(t_read *line, char *msg, int err);
void	close_fds(int fds[2][2], int piper_len);
void	free_piper(t_read *line);
void	cmd_chain(t_read *line, int write[2], int read[2], int cmd);
void	execution_free(t_read *line, int exit_stat);
void	free_piper(t_read *line);
int		execute(t_read *line, char **cmd, char **env);
int		prepare_piper(t_read *line);
int		pipe_execution(t_read *line);
int		execution(t_read *line);
void	heredoc_handler(t_read *line);
void	close_heredocs(int *heredocs, t_read *line);

//signals
void	handle_sigint(int sig);
void	setup_signals(void);
void	ft_signal(int mod);
void	ft_signal2(int mod);
void	ft_signal3(int mod);
#endif
