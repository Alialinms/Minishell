/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:59:30 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/27 22:08:01 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../tokenizer/tokenizer.h"
# include "../expander/ft_expander.h"

# ifndef PATH_MAX
# define PATH_MAX 4096
# endif

typedef struct s_read
{
	int		exit_status;
	char	*prompt;
	char	*line;
	char	*cwd;
	char	**enviro;
	char	**tokens;
	char	**expo;
}				t_read;

int		ft_exit_shell(t_read *line);
void	ft_get_prompt(t_read *line);
void	ft_exit_with_error(t_read *line, char *str, int errno);

#endif
