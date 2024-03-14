/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:26:25 by descamil          #+#    #+#             */
/*   Updated: 2024/03/11 18:16:28 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_count_others(t_mini *mini, char c)
{
	if (c != ' ' && c != '|'/* && c != '\\'*/)
	{
		mini->quotes->other = 1;
		mini->quotes->pipe = 0;
		mini->quotes->o_space = 0;
	}
	else if (c == ' ')
		mini->quotes->o_space = 1;
}

void	ft_count_quotes(t_mini *mini, char c)
{
	printf(GREEN"STR[I] --> %c\n"RESET, c);
	printf(PURPLE"SLASH --> %d\n"RESET, mini->quotes->slash);
	if (c == '\'' && mini->quotes->slash == 0)
		mini->quotes->sim += 1;
	if (mini->quotes->sim == 2)
		mini->quotes->sim = 0;
	if (c == '\"' && mini->quotes->slash == 0)
		mini->quotes->dou += 1;
	if (mini->quotes->dou == 2)
		mini->quotes->dou = 0;
}

void	ft_count_pipes(t_mini *mini, char *str, int i)
{
	if (str[i] == '|' && mini->quotes->dou == 0 && mini->quotes->sim == 0)
	{
		mini->quotes->pipe += 1;
		ft_pipes_error(mini, str, i);
		if (mini->quotes->other == 1)
		{
			mini->quotes->words += 1;
			mini->quotes->other = 0;
			mini->quotes->o_space = 0;
		}
		if (i == 0 || str[i + 1] == '\0' || ft_nothing(str, i + 1) == 1
			|| (mini->quotes->o_space == 1 && str[i + 1] != '|'))
		{
			mini->quotes->o_space = 0;
			if (mini->quotes->error == 0)
				mini->quotes->error = 1;
			if (mini->code_error == NULL && mini->quotes->error != 3)
				mini->code_error = "|";
		}
	}
}

void	ft_count_slash(t_mini *mini, char *str, int i)
{
	if (str[i] == '\\' && mini->quotes->slash == 0)
		mini->quotes->slash = 1;
	else if (str[i] == '\\' && mini->quotes->slash == 1)
		mini->quotes->slash = 0;
}

int	ft_count_words(t_mini *mini, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		printf(GREEN"STR[I] --> %c\n"RESET, str[i]);
		printf(PURPLE"SLASH --> %d\n"RESET, mini->quotes->slash);
		ft_count_slash(mini, str, i);
		ft_count_quotes(mini, str[i]);
		ft_count_others(mini, str[i]);
		ft_count_pipes(mini, str, i);
		if (mini->quotes->error != 0)
			break;
		i++;
	}
	return (mini->quotes->words);
}