/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:44 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/07 16:21:48 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	int start;
	char *input;
	argv[0] = argv[0];
	
	if (argc != 1)
	{
		// Realizar gestion de errores
		printf("Error: Numero de argumentos invalidos.\n");
	}
	else
	{
		ft_set_values(&mini, envp);
		start = 1;
		while(1)
		{
			if (start == 1 && start-- > 0)
				ft_mini_header(&mini);
			//Permancer a la espera
			mini.pwd = ft_find_in_envp("PWD", mini.envp);
			input = readline(mini.pwd);
			// printf("tmp_variable = %s\n", tmp_variable);
			printf("start = %d\n", start);
			break;
		}
	}
	return (0);
}