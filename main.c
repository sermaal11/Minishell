/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:44 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/05 18:40:30 by sergio           ###   ########.fr       */
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

	ft_set_values(&mini, argc, argv, envp);
	start = 1;
	while(1)
	{
		if (start == 1)
		{
			ft_mini_header();
			start = 0;
		}
		// while (envp[i] != NULL)
		// {
		// 	printf("%s\n", envp[i]);
		// 	i++;
		// }
		tmp_variable = ft_find_in_envp(argv[1], envp);
		printf("%s\n", tmp_variable);
		break;
	}
	return (0);
}