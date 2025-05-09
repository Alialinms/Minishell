/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:56:15 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/11 19:40:17 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_with_error(t_read *line, char *str, int i)
{
	int	j;

	if (line->pand)
		ft_free_expander(line->pand);
	if (line->token)
		ft_free_tokenizer(line->token);
	if (line->piper != NULL)
		free_piper(line);
	if (line->prompt != NULL)
		free(line->prompt);
	if (line->cwd != NULL)
		free(line->cwd);
	if (line->enviro != NULL)
		ft_farray(line->enviro);
	if (line->expo != NULL)
		ft_farray(line->expo);
	rl_clear_history();
	if (str)
	{
		//ft_farray(line->tokens);
		free(line->line);
		ft_putendl_fd(str, 2);
	}
	if (line->exit_status == 0)
		line->exit_status = i;
	j = i;
	free (line);
	exit(j);
}
