/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:08:20 by descamil          #+#    #+#             */
/*   Updated: 2024/03/08 18:02:45 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_all_space(t_mini *mini, char *str, int i)
{
	if (str[i] == '\0')
		return (-2);
	if (str[i] == '|')
	{
		mini->code_error = "||";
		return (-1);
	}
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '|')
		{
			mini->code_error = "|";
			return (-1);
		}
		else if (str[i] != ' ')
			return (0);
	}
	return (1);
}

void ft_count_quotes(t_mini *mini, char c)
{
	if (c == '\"' && (mini->quotes->sim % 2 == 1))
	{
		mini->quotes->dou += 1;
		if (mini->quotes->dou % 2 == 0)
			mini->quotes->dou = 0;
		printf("%d\n", mini->quotes->dou);
	}
	if (c == '\'' && (mini->quotes->dou % 2 == 1))
	{
		mini->quotes->sim += 1;
		if (mini->quotes->sim % 2 == 0)
			mini->quotes->sim = 0;
		printf("%d\n", mini->quotes->sim);
	}
}

static int	count_words(t_mini *mini, char *str)
{
	int	words;
	int	space;
	int	i;

	i = 0;
	space = 0;
	words = 1;
	while (str[i] != '\0')
	{
		while (str[i] != '|' && str[i] != '\0')
			ft_count_quotes(mini, str[i++]);
		if (str[i] == '|' && (mini->quotes->dou % 2) == 0 && (mini->quotes->sim % 2) == 0)
		{
			space = ft_all_space(mini, str, ++i);
			if (space == -1)
				return (-1);
			if (space == -2)
				return (-2);
			if (str[i + 1] == '\0' || (space == 1))
			{
				words--;
			}
			words++;
		}
		i++;
	}
	return (words);
}

// static size_t	get_inti_len(const char *str, char value)
// {

// }

// static char	**fill_array(const char *str, char value, char **array, size_t word)
// {
	
// }

// static void	free_memory(size_t row, char **array)
// {
// 	while (row--)
// 		free(array[row]);
// 	free(array);
// }

char	**ft_mini_split(t_mini *mini, char *str)
{
	int	words;
	char	**array;

	if (!str)
		return (NULL);
	words = count_words(mini, str);
	if (words == -1)
	{								/* Salida 258 */
		mini->g_error = 258;
		printf("syntax error near unexpected token `%s'\n", mini->code_error);
		return (NULL);
	}
	if (words == -2)
	{
		return (NULL);
	}	
	printf("Words --> %d\n", words);
	return (NULL);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	// if (!array)
	// 	return (NULL);
	// array = fill_array(str, value, array, word);
	// return (array);
}