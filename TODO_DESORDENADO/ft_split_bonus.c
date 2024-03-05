/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:19:22 by descamil          #+#    #+#             */
/*   Updated: 2024/02/25 17:39:49 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_mod_bonus(const char *s, int i, char c)
{
	int	len;

	len = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0' && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

char	*ft_strlcpy_mod_bonus(char *s, char c, int *new_start, int size)
{
	char	*ptr;
	int		j;
	int		start;

	j = 0;
	start = *new_start;
	ptr = (char *)malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[start] == c && s[start] != '\0')
		start++;
	while (s[start] != '\0' && j < size)
		ptr[j++] = s[start++];
	ptr[j] = '\0';
	*new_start = start;
	return (ptr);
}

void	*free_memory_bonus(int a, char **arr)
{
	int	f;

	f = 0;
	while (f < a)
		free(arr[f++]);
	free(arr);
	return (NULL);
}

int	ft_words_bonus(const char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			word++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (word);
}

char	**ft_split_bonus(const char *s, char c)
{
	int		i;
	int		a;
	int		len_mod;
	char	**arr;
	char	*cpy_mod;

	i = 0;
	a = 0;
	arr = (char **)malloc((ft_words_bonus(s, c) + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (a < ft_words_bonus(s, c))
	{
		len_mod = ft_strlen_mod_bonus(s, i, c);
		cpy_mod = ft_strlcpy_mod_bonus((char *)s, c, &i, len_mod);
		if (cpy_mod == NULL)
			return (free_memory_bonus(a, arr));
		arr[a++] = cpy_mod;
	}
	arr[a] = NULL;
	return (arr);
}
