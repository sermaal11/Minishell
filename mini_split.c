/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:26:43 by descamil          #+#    #+#             */
/*   Updated: 2024/03/09 19:08:11 by descamil         ###   ########.fr       */
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

int	count_quotes_size(t_mini *mini, char c)
{
	if (c == '\'')
		mini->quotes->sim += 1;
	if (mini->quotes->sim == 2)
		mini->quotes->sim = 0;
	if (c == '\"')
		mini->quotes->dou += 1;
	if (mini->quotes->dou == 2)
		mini->quotes->dou = 0;
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
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

int	count_others_size(t_mini *mini, char c)
{
	if (c != ' ' && c != '|')
	{
		mini->quotes->other = 1;
		mini->quotes->pipe = 0;
		mini->quotes->o_space = 0;
	}
	else if (c == ' ')
		mini->quotes->o_space = 1;
	if (c != '|')
		return (1);
	return (0);
}

void	pipes_error(t_mini *mini, char c)
{
	printf(RED"STR[i + 1] --> [%c]\n"RESET, c);
	printf(PURPLE"OTHER --> [%d]\n"RESET, mini->quotes->other);
	if (c == '|' && mini->quotes->other == 0 ) /* Error "||" */
	{
		mini->quotes->error = 1;
		printf(ORANGE"ERROR = [%d]\n"RESET, mini->quotes->error);
		mini->code_error = "||";
	}
	else if (mini->quotes->pipe == 2) /* Error "|   |" */
	{
		mini->quotes->error = 1;
		mini->code_error = "|";
	}
}

int	ft_nothing(char *str, int i)
{
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
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
		if (i == 0 || str[i + 1] == '\0' || ft_nothing(str, i + 1) == 1
			|| (mini->quotes->o_space == 1 && str[i + 1] != '|'))
		{
			mini->quotes->o_space = 0;
			mini->quotes->error = 1;
			if (mini->code_error == NULL)
				mini->code_error = "|";
		}
	}
}

// int	count_pipes_size(t_mini *mini, char *str, int i)
// {
// 	if (str[i] == '|' && mini->quotes->dou == 0 && mini->quotes->sim == 0)
// 	{
// 		mini->quotes->final = i - 1; /* EJ = "cat |" I == 5 FINAL == 4 */
// 		return (0);
// 	}
// }

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
		printf("Wait to close\n");
		return (-1);
	}
	return (0);
}

// char	**fill_array(t_mini *mini, char *str, char **array, int words)
// {
// 	int	i;
// 	int	j;
// 	int	k;
// 	int	l;
// 	int	size;

// 	i = -1;
// 	j = 0;
// 	k = 0;
// 	l = 0;
// 	size = 0;
// 	while (str[++i] != '\0')
// 	{
// 		size += count_quotes_size(mini, str[i]);
// 		size += count_others_size(mini, str[i]);
// 		size += count_pipes_size(mini, str, i);
		
// 	}
// 	return (NULL);
// }

char	**mini_split(t_mini *mini, char *str)
{
	// char	**array;
	int		words;
	
	if (str == NULL)
		return (NULL);
	words = count_words(mini, str);
	printf("%d\n", mini->quotes->error);
	if (ft_words_errors(mini) == -1)
		return (NULL);
	printf(GREEN"Words --> "RESET YELLOW"%d\n"RESET, words);
	// array = (char **)malloc((words + 1) * sizeof(char *));
	// if (array == NULL)
	// 	return (NULL);
	// array = fill_array(mini, str, array, words);
	// return (array);
	return (NULL);
}
