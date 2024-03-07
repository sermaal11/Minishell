/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:57:33 by sergio            #+#    #+#             */
/*   Updated: 2024/03/07 16:21:53 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_varible(char *dst, const char *var_content)
{
	int num;
	int i;

	num = 0;
	i = 0;
	while (var_content[num] != '=')
		num++;
	while (var_content[++num] != '\0')
		dst[i++] = var_content[num];
	while (dst[i] != '\0')
		dst[i++] = '\0';
	return (dst);
}

void	ft_set_values(t_mini *mini, char **envp)
{
	mini->envp = envp;
}

char	*ft_find_in_envp(char *variable, char** envp)
{
	int i;
	char *temp;

	i = -1;
	variable = ft_strjoin(variable, "=");
	//printf("Variable -> %s\n", variable);
	while(envp[++i] != NULL)
	{
		if (ft_strnstr(envp[i], variable, ft_strlen(variable)) != NULL)
		{
			temp = ft_remove_varible(envp[i], envp[i]);
			return (temp);
		}
	}
	return (NULL);
}

void	ft_mini_header(t_mini *mini)
{
	execve("/usr/bin/clear", "clear", mini->envp);
	write (1, "\t\n", 3);
	write (1, "\t __  __ ___ _  _ ___ ___ _  _ ___ _    _  \n", 45);
	write (1, "\t|  \\/  |_ _| \\| |_ _/ __| || | __| |  | |\n", 44);
	write (1, "\t| |\\/| || || .` || |\\__ \\ __ | _|| |__| |__ \n", 47);
	write (1, "\t|_|  |_|___|_|\\_|___|___/_||_|___|____|____|\n", 47);
	write (1, "\t\n", 3);
	write (1, "\t\n", 3);
	}


   


                                             

