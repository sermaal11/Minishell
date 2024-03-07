/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:44 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/07 12:13:40 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	int start;
	int i;

	i = 0;
	char *tmp_variable;

	ft_set_values(&mini, argv, envp, argc);
	start = 1;
	while(1)
	{
		if (start == 1)
		{
			ft_mini_header();
			start = 0;
		}
		//Localizar e imprimir la variable pwd
		//Permancer a la espera
		tmp_variable = ft_find_in_envp(argv[1], mini.envp);
		printf("tmp_variable = %s\n", tmp_variable);

		break;
	}
	return (0);
}