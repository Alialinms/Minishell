/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 23:02:20 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/16 19:52:07 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t   g_sig;


void	initalization_struct_pand(t_read *line)
{
	line->pand = malloc(sizeof(t_expand));
	if (!line->pand)
		exit (0);
	line->pand->i = 0;
	line->pand->i_result = 0;
	line->pand->i_size = 0;
	line->pand->count = 0;
	line->pand->j = 0;
	line->pand->count = 0;
	line->pand->k = 0;
	line->pand->i_malloc = 0;
	line->pand->last_exit_code = NULL;
	line->pand->string = NULL;
	line->pand->argv = NULL;
	line->pand->quoted = NULL;
	line->pand->input = NULL;
	line->pand->var_name = NULL;
	line->pand->var_value = NULL;
	line->pand->result = NULL;
	line->pand->envment = NULL;
}

void	initalization_struct_tok(t_read *line)
{
	line->token = malloc(sizeof(t_tok));
	if (!line->token)
		exit (0);
	line->token->i = 0;
	line->token->index = 0;
	line->token->j = 0;
	line->token->count = 0;
	line->token->k = 0;
	line->token->error_token = 1;
	line->token->c = '\0';
	line->token->input = NULL;
	line->token->tokens = NULL;
}
void	initalization(t_read *line, char **envp)
{
	initalization_struct_pand(line);
	initalization_struct_tok(line);
	ft_bzero(line->heredocs, sizeof(line->heredocs));
	line->line = NULL;
	line->prompt = NULL;
	line->tokens = NULL;
	line->cwd = NULL;
	line->piper = NULL;
	line->enviro = ft_cpyarr(envp);
	line->exit_status = 0;
	line->piper_len = 0;
	if (!line->enviro)
	{
		ft_putendl_fd("Enviro err: no ENV variable or no memory", 2);
		exit (1);
	}
	line->expo = ft_cpyarr(line->enviro);
	if (!line->expo)
	{
		ft_putendl_fd("Expo err: no Memory for expo", 2);
		ft_farray(line->enviro);
		exit (1);
	}
}

void	ft_get_prompt(t_read *line)
{
	char	temp[PATH_MAX];

	getcwd(temp, sizeof(temp));
	if (line->cwd)
		free(line->cwd);
	if (line->prompt)
		free(line->prompt);
	line->cwd = ft_strdup(temp);
	if (ft_fetcharr(line->enviro, "HOME="))
	{
		line->cwd = ft_remove_str(line->cwd ,(ft_fetcharr(line->enviro, "HOME=") + 5));
		line->prompt = ft_joinstrjoin("Minishell>: ~", line->cwd, "$ ");
	}
	else
		line->prompt = ft_joinstrjoin("Minishell>:", temp, "$ ");
	if (!line->prompt || !line->cwd)
		ft_exit_with_error(line, "Unable to get prompt", 1);
}

int		main(int argc, char **argv, char **envp)
{
	t_read	*line = malloc(sizeof(t_read));
	if (!line)
		exit (0);
	(void) argc;
	(void) argv;
	initalization(line, envp);
	ft_get_prompt(line);
	//if (g_sig == 0)
	//setup_signals();
	while (1)
	{
		ft_signal(1);
		if (g_sig == 0)
			line->line = readline(line->prompt);
		else
			line->line = readline(NULL);
		if (g_sig == 1)
		{
			//g_sig = 0;
			line->exit_status = 130;	
		}
		add_history(line->line);
		line->line = ft_expander(line, ft_itoa(line->exit_status), argv[0]);
		line->tokens = ft_tokenizer(line);
		if (ft_exit_shell(line))
			break;
		terminal_shell(line);
		ft_farray(line->tokens);
		free_piper(line);
		initialize_tok(line->token);
		//line->exit_status = 0;
	}
	ft_exit_with_error(line , NULL, 0);
	return (line->exit_status);
}
