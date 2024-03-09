/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:08:20 by descamil          #+#    #+#             */
/*   Updated: 2024/03/09 15:26:26 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_all_space(t_mini *mini, char *str, int i, int other_char)
{
	int	space;

	space = 0;
	while (str[i] == ' ' || str [i] == '\0' || str[i] == '|')
	{
		if (str[i] == '|')
		{
			mini->code_error = "||";
			return (-1);
		}
		while (str[i++] == ' ')
		{
			if (str[i] != ' ' || str[i] != '\0' || str[i] != '|')
			{
				space = 0;
				break;
			}
			space = 1;
		}
		if (str[i] == '\0')
			return(-2);
		if (str[i] == '\0' && other_char == 0)
		{
			mini->code_error = "|";
			return (-1);
		}
		i++;
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
		if (mini->quotes->dou == 2)
			mini->quotes->dou = 0;
	}
	if (c == '\'')
	{
		mini->quotes->sim += 1;
		if (mini->quotes->sim == 2)
			mini->quotes->sim = 0;
	}
	// printf("%d\n", mini->quotes->dou);
}

static int	count_words(t_mini *mini, char *str)
{
	int	other_char;
	int	words;
	int	space;
	int	i;

	i = 0;
	space = 0;
	words = 1;
	other_char = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '|' && str[i] != '\0' && str[i] != ' ')
		{
			ft_count_quotes(mini, str[i++]);
			other_char = 1;
		}
		while (str[i] == ' ')
		{
			if (str[i + 1] == '|' && other_char == 0)
			{
				mini->code_error = "|";
				if (str[i + 2] == '|')
					mini->code_error = "||";
				return (-1);
			}
			else if (i + 1 == '|' && other_char == 1)
				return (-2);
			i++;
		}
		if (str[i] == '|' && (mini->quotes->dou % 2) == 0 && (mini->quotes->sim % 2) == 0)
		{
			space = ft_all_space(mini, str, ++i, other_char);
			if (space == -1)
				return (-1);
			if (space == -2)
				return (-2);
			if (str[i + 1] == '\0' || (space == 1))
				words--;
			words++;
		}
		i++;
	}
	return (words);
}

char **ft_fill_array(t_mini *mini, char *str, char **array_to_fill, int words)
{
	int	size;
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	j = 0;
	k = 0;
	size = 0;
	while (k < words)
	{
		while (str[j] != '\0')
		{
			ft_count_quotes(mini, str[j]);
			if (str[j] == '|' && mini->quotes->dou == 0 && mini->quotes->sim == 0)
			{
				j++;
				break;
			}
			size++;
			j++;
		}
		// printf(RED"%d\n"RESET, mini->quotes->dou);
		// printf("%d\n", mini->quotes->sim);
		if (mini->quotes->dou == 1 || mini->quotes->sim == 1)
		{
			printf("Close quotes\n");
			break;
		}
		if (size > 0 && mini->quotes->dou == 0 && mini->quotes->sim == 0)
		{
			array_to_fill[k] = (char *)malloc((size + 1) * sizeof(char));
			if (array_to_fill[k] == NULL)
				return (NULL);
			// printf("Size0 = %d\n", size);
			l = 0;
			while (size > 0)
			{
				array_to_fill[k][l] = str[i];
				l++;
				i++;
				size--;
			}
			array_to_fill[k][l] = '\0';
			i++;
			// printf("Size1 = %d\n", size);
			array_to_fill[k][i] = '\0';
			// printf(GREEN"ARRAY --> %s\n"RESET, array_to_fill[k]);
			k++;
		}
		else
			k++;
		// exit(0);
	}
	array_to_fill[k] = NULL;
	return (array_to_fill);
}

char	**ft_mini_split(t_mini *mini, char *str)
{
	char	**filled_array;
	int		words;

	if (!str)
		return (NULL);
	words = count_words(mini, str);
	// printf(YELLOW"ERROR == %d\n"RESET, words);
	if (words == -1)
	{								/* Salida 258 */
		mini->g_error = 258;
		printf("mini: syntax error near unexpected token `%s'\n", mini->code_error);
		// printf("Aquí\n");
		return (NULL);
	}
	else if (words == -2)
	{
		printf("Wait to close\n");
		return (NULL);
	}
	// printf("Words --> %d\n", words);
	filled_array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!filled_array)
		return (NULL);
	filled_array = ft_fill_array(mini, str, filled_array, words);
	return (filled_array);
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