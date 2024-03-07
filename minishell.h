/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/07 12:09:57 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

# define R 0
# define W 1

typedef struct s_mini
{
	// Incializamos desde el main
	int argc;
	char **argv;
	char **envp;
}	t_mini;

typedef struct s_argv
{
	char **split_argv;
}	t_argv;

void	ft_mini_header(void);
void	ft_set_values(t_mini *mini, char **argv, char **envp, int argc);
char	*ft_find_in_envp(char *variable, char** envp);

#endif