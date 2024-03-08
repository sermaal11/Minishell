/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:08:20 by descamil          #+#    #+#             */
/*   Updated: 2024/03/08 19:46:13 by descamil         ###   ########.fr       */
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
	if (c == '\"')
	{
		mini->quotes->dou += 1;
		if (mini->quotes->dou % 2 == 0)
			mini->quotes->dou = 0;
	}
	if (c == '\'')
	{
		mini->quotes->sim += 1;
		if (mini->quotes->sim % 2 == 0)
			mini->quotes->sim = 0;
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

char **ft_fill_array(t_mini *mini, char *str, char **array_to_fill, int words) //t_mini *mini,
{
	int	k;
	int	j;
	int	size;
	int	i;
	int	l;

	i = 0;
	k = 0;
	j = 0;
	size = 0;
	while (k < words)
	{
		while (str[j] != '\0')
		{
			ft_count_quotes(mini, str[j]);
			printf("D = %d\n", mini->quotes->dou);
			printf("S = %d\n", mini->quotes->sim);
			if (str[j] == '|' && mini->quotes->dou == 0 && mini->quotes->sim == 0)
			{	
				j++;
				break;
			}
			size++;
			j++;
		}
		array_to_fill[k] = (char *)malloc((size + 1) * sizeof(char));
		l = 0;
		printf("Size0 = %d\n", size);
		while (size > 0)
		{
			array_to_fill[k][l] = str[i];
			l++;
			i++;
			size--;
		}
		array_to_fill[k][l] = '\0';
		i++;
		printf("Size1 = %d\n", size);
		array_to_fill[k][i] = '\0';
		printf(GREEN"ARRAY --> %s\n"RESET, array_to_fill[k]);
		k++;
		// exit(0);
	}
	return (array_to_fill);
}

// static char	**fill_array(const char *str, char value, char **array, size_t word)
// {
	
// }

// static void	free_memory(size_t k, char **array)
// {
// 	while (k--)
// 		free(array[k]);
// 	free(array);
// }

char	**ft_mini_split(t_mini *mini, char *str)
{
	char	**filled_array;
	int		words;

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
	filled_array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!filled_array)
		return (NULL);
	filled_array = ft_fill_array(mini, str, filled_array, words); //mini,
	return (filled_array);
}