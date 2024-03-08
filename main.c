/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:44 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/08 16:30:04 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

int main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	char	**input_matrix;
	// int		i;
		
	if (argc != 1)
		printf("Error: Numero de argumentos invalidos.\n");
	else
	{
		ft_set_values(&mini, argv ,envp);
		while(1)
		{
			ft_initialize(&mini);
			if (ft_invalid_expr(&mini) == -1 || mini.input[0] == '\0')
				ft_not_variable();
			else
			{
				add_history(mini.input);
				input_matrix = ft_mini_split(&mini, mini.input);
				// ! A tener en cuenta echo "hola | que tal"
				// ! echo "hola"que"tal"
				// ! un argumento es todo hasta el sguiente espacio no entrecomillado
				
				// if (ft_strncmp(mini.input, "exit", ft_strlen("exit")) == 0)
				// {
				// 	printf("exit\n");
				// 	free(mini.input);
				// }
			}
			if (mini.input != NULL)
				free(mini.input);
			// break;
		}
		
	}
	atexit(leaks);
	return (0);
}