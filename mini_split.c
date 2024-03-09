/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:26:43 by descamil          #+#    #+#             */
/*   Updated: 2024/03/09 17:55:42 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_quotes(t_mini *mini, char c)
{
	if (c == '\'')
		mini->quotes->sim += 1;
	if (mini->quotes->sim == 2)
		mini->quotes->sim = 0;
	if (c == '\"')
		mini->quotes->dou += 1;
	if (mini->quotes->dou == 2)
		mini->quotes->dou = 0;
}

void	count_others(t_mini *mini, char c)
{
	if (c != ' ' && c != '|')
	{
		mini->quotes->other = 1;
		mini->quotes->pipe = 0;
		mini->quotes->o_space = 0;
	}
	else if (c == ' ')
		mini->quotes->o_space = 1;
}

void	pipes_error(t_mini *mini, char c)
{
	printf(RED"STR[i + 1] --> [%c]\n", c);
	printf(PURPLE"OTHER --> [%d]\n", mini->quotes->other);
	if (c == '|' && mini->quotes->other == 0 ) /* Error "||" */
	{
		mini->quotes->error = 1;
		printf(ORANGE"ERROR = [%d]\n"RESET, mini->quotes->error);
		mini->code_error = "||";
		return ;
	}
	else if (mini->quotes->pipe == 2) /* Error "|   |" */
	{
		mini->quotes->error = 1;
		mini->code_error = "|";
	}
}

void	count_pipes(t_mini *mini, char *str, int i)
{
	if (str[i] == '|' && mini->quotes->dou == 0 && mini->quotes->sim == 0)
	{
		printf(BLUE"BLUE\n"RESET);
		mini->quotes->pipe += 1;
		pipes_error(mini, str[i + 1]);
		if (mini->quotes->other == 1)
		{
			mini->quotes->words += 1;
			mini->quotes->other = 0;
		}
		if (mini->quotes->o_space == 1 && str[i + 1] != '|')
		{
			mini->quotes->o_space = 0;
			mini->quotes->error = 1;
			mini->code_error = "|";
		}
	}
}

int	count_words(t_mini *mini, char *str)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		count_quotes(mini, str[i]);
		count_others(mini, str[i]);
		count_pipes(mini, str, i);
		if (mini->quotes->error != 0)
			break;
	}
	return (mini->quotes->words);
}

// int	ft_words_errors(t_mini *mini)
// {
	
// 	return (0);
// }

char	**mini_split(t_mini *mini, char *str)
{
	// char	**array;
	int		words;
	
	if (str == NULL)
		return (NULL);
	words = count_words(mini, str);
	printf(GREEN"Words --> "RESET YELLOW"%d\n"RESET, words);
	printf("%d\n", mini->quotes->error);
	if (mini->quotes->error == 1)
	{
		mini->g_error = 258;
		printf("mini: syntax error near unexpected token `%s'\n", mini->code_error);
		return (NULL);
	}
	else if (mini->quotes->error == 2 || mini->quotes->dou == 1 || mini->quotes->dou == 1)
	{
		printf("Wait to close\n");
		return (NULL);
	}
	return (NULL);
}
	// if (ft_words_errors(mini) == -1)
	// 	return (NULL);
	// array = (char **)malloc((words + 1) * sizeof(char *));
	// if (array == NULL)
	// 	return (NULL);
	// array = fill_array(mini, str, array, words);
	// return (array);