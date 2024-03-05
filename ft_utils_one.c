/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:57:33 by sergio            #+#    #+#             */
/*   Updated: 2024/03/05 19:04:04 by sergio           ###   ########.fr       */
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

	i = 0;
	//tmp_variable = ft_strjoin(variable, "=");
	while(envp[i++] != NULL)
	{
		if (ft_strnstr(envp[i], variable, ft_strlen(variable)))
			return (envp[i]);
	}
	return ("");
}

void	ft_mini_header(void)
{
	write (1, "\t                                                      \n", 57);
	write (1, "\t _  _   __   __ _   __   ____  _  _  ____  __    __   \n", 57);
	write (1, "\t( \\/ ) (  ) (  ( \\ (  ) / ___)/ )( \\(  __)(  )  (  )  \n", 57);
	write (1, "\t/ \\/ \\  )(  /    /  )(  \\___ \\) __ ( ) _) / (_/\\/ (_/\\\n", 57);
	write (1, "\t\\_)(_/ (__) \\_)__) (__) (____/\\_)(_/(____)\\____/\\____/\n", 57);
	write (1, "\t                                                      \n", 57);
	write (1, "\t                                                      \n", 57);
}
