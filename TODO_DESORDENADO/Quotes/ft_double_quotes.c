/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:19:30 by descamil          #+#    #+#             */
/*   Updated: 2024/03/05 17:32:35 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size_total;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	size_total = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * (size_total + 1));
	if (ptr == NULL)
		return (NULL);
	while ((char *)s1 && (char)s1[i] != '\0')
		ptr[j++] = (char)s1[i++];
	j = 0;
	while ((char *)s2 && (char)s2[j] != '\0')
		ptr[i++] = (char)s2[j++];
	ptr[i] = '\0';
	if (!s1)
		free((char *)s1);
	return (ptr);
}

int	ft_count_quotes(t_data *data)
{
	int	size;
	int	i = 0;
	
	size = ft_strlen(data->str);
	while (size-- > 0)
	{
		if (data->str[i] == '\"')
			data->d_quote++;
		else if (data->str[i] == '\'')
			data->s_quote++;
		i++;
	}
	if (data->d_quote % 2 != 0 || data->s_quote % 2 != 0)
		return (0);
	if ((data->s_quote + data->d_quote) == ft_strlen(data->str))
		return (0);
	if (data->d_quote == 0)
		data->d_quote = -1;
	if (data->s_quote == 0)
		data->s_quote = -1;
	return (1);
}

char	*ft_remove(char *dst, const char *src, int num)
{
	int i;

	i = 0;
	while (src[num] != '\0')
		dst[i++] = src[num++];
	while (dst[i] != '\0')
		dst[i++] = '\0';
	return (dst);
}

char	*ft_find(t_data *data, char *str)
{
	char	*any;
	int		i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if(ft_strnstr(data->envp[i], str, ft_strlen(str)) == 1)
		{
			any = data->envp[i];
			any = ft_remove(any, any, ft_strlen(str));
			return (any);
		}
		i++;
	}
	return ("");
}

char	*ft_divjoin(char *str, char *any, int i)
{
	char 	*tmp;
	char	*final;
	int		length;
	int		j;
	int		k;
	int		l;

	k = i;
	l = i;
	j = 0;
	length = 0;
	while (str[l] != '\"')
		l++;
	k = l;
	while (str[k++] != '\0')
		length++;
	tmp = malloc(length + 1);
	if (tmp == NULL)
		return (NULL);
	while (str[l] != '\0')
		tmp[j++] = str[l++];
	tmp[j] = '\0';
	str = ft_set_zero(str, i);
	final = ft_strjoin(str, any);
	final = ft_strjoin(final, tmp);
	free(tmp);
	return (final);
}

int	ft_translate(t_data *data, int i)
{
	char	*tmp;
	char	*any;
	int		k;
	int		j;
	
	k = i;
	//(Añadir isnum)
	while (data->str[k + data->len_var] != '\0' && data->str[k + data->len_var] != '\"' && data->str[k + data->len_var] != '\'')
		data->len_var++;
	tmp = malloc(data->len_var + 2);
	if (tmp == NULL)
		return (0);
	j = 0;
	//(Añadir isnum)
	while (data->str[k + j] != '\0' && data->str[k] != '\"' && data->str[k] != '\'')
		tmp[j++] = data->str[k++];
	tmp[j++] = '=';
	any = ft_find(data, tmp);
	free(tmp);
	printf(RED"ANY = %s\n"RESET, any);
	data->str = ft_divjoin(data->str, any, i);
	return (ft_strlen(any));
}

int	ft_double_quotes(t_data *data, int i, int q, int valid)
{
	//int	prev;
	int	j;

	j = 0;
	//prev = 0;
	if ((valid % 2) == 5 && data->str[i] == q && data->str[i + 1] == q)
		return (i + 2);
	else
	{
		i++;
		while (data->str[i] != q && data->str[i] != '$' && data->str[i] != '\0')
		{
			data->command_len++;
			i++;
		}
		if (data->str[i] == '$')
		{
			j = ft_translate(data, ++i);
			printf("J == %d\n", j);
		}
		return (i);
	}
	return (-1);
}
			// if (data->str[i] == '$')
			// {
			// 	data->command_len = ft_translate(data, i + 1);
			// 	i += (data->command_len - prev);
			// }

// int	ft_double_quotes(t_data *data, int i, int q, int valid)
// {
// 	int	prev;

// 	prev = data->command_len;
// 	printf(BLUE"Nº --> %d = %c\n"RESET, i, data->str[i]);
// 	if ((valid % 2) == 5 && data->str[i] == q && data->str[i + 1] == q)
// 		return (i + 2);
// 	else
// 	{
// 		i++;
// 		printf(BLUE"Nº --> %d = %c\n"RESET, i, data->str[i]);
// 		while (data->str[i] != q && data->str[i] != '\0')
// 		{
// 			if (data->str[i] == '$')
// 			{
// 				data->command_len = ft_translate(data, i + 1);
// 				i += (data->command_len - prev);
// 			}
// 			else
// 			{
// 				printf(YELLOW"Nº --> 		%d = %c\n"RESET, i, data->str[i]);
// 				if ((valid % 2) == 5 && data->str[i + 2] == '\0' && data->str[i + 1] != q)
// 				{
// 					printf(YELLOW"I = 	%d\n"RESET, i);
// 					return (-1);
// 				}
// 				data->command_len++;
// 				i++;
// 				printf(YELLOW"LEN = 	%d\n"RESET, data->command_len);
// 			}
// 		}
// 		return (i);
// 	}
// 	return (-1);
// }
