/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:59:30 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/11 19:53:13 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../expander/ft_expander.h"
# include "../tokenizer/tokenizer.h"

# ifndef PATH_MAX
# define PATH_MAX 4096
# endif

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
void	ft_exit_with_error(t_read *line, char *str, int errno);
void	terminal_shell(t_read *line);
//expander
//int & size_t
int	comper_expander(char c);
int string_expander(char c);
size_t	count_malloc(t_expand *pand);

//char
char	*ft_expander(t_read *line, char *last_exit_code, char *argv);
char	*get_string_expander(t_expand *pand);

//void
void	ft_free_expander(t_expand *pand);
void	dollar_malloc_expander(t_expand *pand);
void	dollar_fill_expander(t_expand *pand);
void	single_quoted(t_expand *pand);
void	fill_value_expander(t_expand *pand, char *value);
void	var_expander(t_expand *pand);
void	initialize_pand(t_expand *pand);
//tokenizer
char	**ft_tokenizer(t_read *line);
void	ft_free_tokenizer(t_tok *token);
void	greater_tokenizer(t_tok *token);
void	pipe_tokenizer(t_tok *token);
void	dollar_tokenizer(t_tok *token);
void	string_tokenizer(t_tok *token);
void	initialize_tok(t_tok *token);
//Builtin
void	builtin_part1(t_read *line, char **cmd);
void	ft_handle_cd(t_read *line, char **cmd);
void	ft_handle_echo(char **cmd);
void	ft_handle_export(t_read *line, char **cmd);
void	ft_handle_unset(t_read *line, char **cmd);
void	ft_handle_env(t_read *line, char **cmd);

//execution
int		prepare_piper(t_read *line);
int		execution(t_read *line);
void	free_piper(t_read *line);

#endif
