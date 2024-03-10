/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:44 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/10 09:53:18 by descamil         ###   ########.fr       */
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
	int		i;
	int		j;
	
	input_matrix = NULL;
	if (argc != 1)
		printf("Error: Numero de argumentos invalidos.\n");
	else
	{
		ft_set_values(&mini, argv ,envp);
		i = 0;
		while(i++ < 10)
		{
			ft_initialize(&mini);
			if (ft_invalid_expr(&mini) == -1 || mini.input[0] == '\0')
				ft_not_variable();
			else
			{
				mini.quotes->dou = 0;
				mini.quotes->sim = 0;
				mini.quotes->pipe = 0;
				mini.quotes->other = 0;
				mini.quotes->error = 0;
				mini.quotes->words = 1;
				add_history(mini.input);
				input_matrix = mini_split(&mini, mini.input);
				// if (input_matrix == NULL)
				// {
				// 	if (mini.input != NULL)
				// 		free(mini.input);
				// 		mini.input = NULL;
				// }
				// A tener en cuenta echo "hola | que tal"
				// echo "hola"que"tal"
				// un argumento es todo hasta el sguiente espacio no entrecomillado
				
				// if (ft_strncmp(mini.input, "exit", ft_strlen("exit")) == 0)
				// {
				// 	printf("exit\n");
				// 	free(mini.input);
				// }
				j = 0;
				mini.code_error = 0;
				if (input_matrix != NULL)
				{
					while (input_matrix[j] != NULL)
						free(input_matrix[j++]);
					free(input_matrix);
				}
			}
			if (mini.input != NULL)
				free(mini.input);
			// if (mini.input != NULL)
			// {
			// 	free(mini.input);
			// 	mini.input = NULL;
			// }
			// if (input_matrix != NULL)
			// {
			// 	while (input_matrix[i] != NULL)
			// 		free(input_matrix[i++]);
			// 	free(input_matrix);
			// }
		}
		
	}
	atexit(leaks);
	return (0);
}
