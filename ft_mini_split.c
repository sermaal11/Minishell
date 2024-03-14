/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:26:43 by descamil          #+#    #+#             */
/*   Updated: 2024/03/11 18:00:07 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_quotes_size(t_mini *mini, char *str, int i)
{
	char	c;
	char	a;
	
	c = str[i];
	if (i != 0)
		a = str[0];
	else
		a = str[i - 1];
	if (c == '\''/*&& a != '\\'*/)
		mini->quotes->sim += 1;
	if (mini->quotes->sim == 2)
		mini->quotes->sim = 0;
	if (c == '\"'/*&& a != '\\'*/)
		mini->quotes->dou += 1;
	if (mini->quotes->dou == 2)
		mini->quotes->dou = 0;
	return (0);
}

int	ft_count_others_size(t_mini *mini, char c)
{
	if (c != '|')
		return (1);	
	else if (c == '|' && (mini->quotes->dou == 1 || mini->quotes->sim == 1))
		return (1);
	return (0);
}

int	ft_count_pipes_size(t_mini *mini, char *str, int i)
{
	if (str[i] == '|' && mini->quotes->dou == 0 && mini->quotes->sim == 0 /*&& ((str[i - 2] == '\\' && str[i - 1]  == '\\') || str[i - 1] != '\\')*/)
	{
		mini->quotes->words--;
		mini->quotes->stop = 1;
		return (0);	/* EJ = "cat |" I == 5 FINAL == 4 */
	}
	// if (str[i - 2] == '\\' && str[i - 1]  == '\\')
	// 	return (1);
	return (0);
}

int *ft_words_size(t_mini *mini, char *str)
{
	int	*tmp;
	int	size;
	int j;
	int	i;
	
	j = 0;
	i = 0;
	tmp = (int *)malloc(mini->quotes->words * sizeof(int *));
	while (mini->quotes->words > 0 && str[i] != '\0')
	{
		size = 0;
		while (str[i] != '\0' && mini->quotes->stop != 1)
		{
			printf(BOLD_BLUE"%c\n"RESET, str[i]);
			size += ft_count_quotes_size(mini, str, i);
			size += ft_count_others_size(mini, str[i]);
			size += ft_count_pipes_size(mini, str, i);
			i++;
		}
		if (mini->quotes->stop == 1)
			mini->quotes->stop = 0;
		tmp[j++] = size;
		printf(RED"SIZE = %d\n"RESET, size);
		printf(RED"TMP = %d\n"RESET, tmp[j - 1]);
	}
	return (tmp);
}

char **ft_memory(t_mini *mini, int *tmp, char **array, char *str)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		printf("POS -> %dº Nº -> %d\n", i, tmp[i]);
		i++;
	}
	// if (array != NULL)
	// {
	// 	while (array[i])
	// 	{
	// 		printf(BOLD_CYAN"POS -> %dº"GREEN RESET"CHAR -> %s"RESET, i, array[i]);
	// 		i++;
	// 	}
	// }
	array = NULL;
	printf(BOLD_CYAN"CHAR -> %s\n"RESET, str);
	mini->start += 0;
	return (NULL);
}

char	**fill_array(t_mini *mini, char *str, char **array)
{
	int	*tmp;
	
	tmp = ft_words_size(mini, str);
	array = ft_memory(mini, tmp, array, str);

	return (NULL);
}


















char	**ft_mini_split(t_mini *mini, char *str)
{
	char	**array;
	
	if (str == NULL)
		return (NULL);
	mini->quotes->words = ft_count_words(mini, str);
	printf("ERROR = %d\n", mini->quotes->error);
	if (ft_words_errors(mini) == -1)
		return (NULL);
	printf(GREEN"Words --> "RESET YELLOW"%d\n"RESET, mini->quotes->words);
	array = (char **)malloc((mini->quotes->words + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = fill_array(mini, str, array);
	return (array);
}
