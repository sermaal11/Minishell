/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:57:33 by sergio            #+#    #+#             */
/*   Updated: 2024/03/07 12:44:43 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_values(t_mini *mini, char **argv, char **envp, int argc)
{
	mini->argv = argv;
	mini->envp = envp;
	mini->argc = argc;
}

char	*ft_find_in_envp(char *variable, char** envp)
{
	int i;

	i = -1;
	variable = ft_strjoin(variable, "=");
	//printf("Variable -> %s\n", variable);
	while(envp[++i] != NULL)
	{
		if (ft_strnstr(envp[i], variable, ft_strlen(variable)) != NULL)
			return (envp[i]);
	}
	return (NULL);
}

void	ft_mini_header(void)
{
	write (1, "\t\n", 3);
	write (1, "\t __  __ ___ _  _ ___ ___ _  _ ___ _    _  \n", 45);
	write (1, "\t|  \\/  |_ _| \\| |_ _/ __| || | __| |  | |\n", 44);
	write (1, "\t| |\\/| || || .` || |\\__ \\ __ | _|| |__| |__ \n", 47);
	write (1, "\t|_|  |_|___|_|\\_|___|___/_||_|___|____|____|\n", 47);
	write (1, "\t\n", 3);
	}


   


                                             

