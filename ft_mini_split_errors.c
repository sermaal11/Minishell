/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:29:49 by descamil          #+#    #+#             */
/*   Updated: 2024/03/11 17:13:30 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipes_error(t_mini *mini, char *str, int i)
{
	if (str[i + 1] == '|' && mini->quotes->other == 0 ) /* Error "||" */
	{
		mini->quotes->error = 1;
		mini->code_error = "||";
	}
	else if (mini->quotes->pipe == 2) /* Error "|   |" */
	{
		mini->quotes->error = 1;
		mini->code_error = "|";
		if (str[i - 1] == '|' && str[i] == '|' && ft_nothing(str, i + 1) == 1)
			mini->code_error = "||";
		else if ((str[i - 1] == '|' && str[i] == '|') && ft_nothing(str, i + 1) == 0)
		{
			mini->quotes->error = 3;
			mini->code_error = NULL;
		}
	}
}

int	ft_words_errors(t_mini *mini)
{
	if (mini->quotes->error == 1)
	{
		mini->g_error = 258;
		printf("mini: syntax error near unexpected token");
		printf("`%s'\n", mini->code_error);
		return (-1);
	}
	else if (mini->quotes->error == 2 || mini->quotes->dou == 1
			|| mini->quotes->dou == 1)
	{
		printf("Wait to close quotes\n");
		return (-1);
	}
	else if (mini->quotes->error == 3)
	{
		printf ("Error double pipes\n");
		return (-1);
	}
	return (0);
}
