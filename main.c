/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:44 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/08 12:34:09 by smarin-a         ###   ########.fr       */
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
		
	if (argc != 1)
		printf("Error: Numero de argumentos invalidos.\n");
	else
	{
		ft_set_values(&mini, argv ,envp);
		while(1)
		{
			ft_initialize(&mini);
			printf("==> [%s]\n", mini.input);
			if (ft_invalid_expr(&mini) == -1 || mini.input[0] == '\0')
				ft_not_variable();
			else
			{
				add_history(mini.input);
				
				input_matrix = ft_split(mini.input, '|');
				if (!input_matrix)
					return (0);
				

				// ! A tener en cuenta echo "hola | que tal"
				// ! echo "hola"que"tal"
				// ! un argumento es todo hasta el sguiente espacio no entrecomillado
				i = 0;
				while(input_matrix[i])
				{
					printf("input_matrix = %s\n",input_matrix[i++]);
				}
				
				if (ft_strncmp(mini.input, "exit", ft_strlen("exit")) == 0)
				{
					printf("exit\n");
					free(mini.input);
					
					//liberamos la matrix en caso de encontrar exit
					ft_free_matrix(input_matrix);
					free(input_matrix);
					input_matrix = NULL;
					break;
				}
				
				//Libramos la matrix
				ft_free_matrix(input_matrix);
				free(input_matrix);
				input_matrix = NULL;
			}
			if (mini.input != NULL)
				free(mini.input);
			// break;
		}
		
	}
	atexit(leaks);
	return (0);
}