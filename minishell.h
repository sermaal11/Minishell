/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/07 16:06:11 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	"./libft/libft.h"
# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<dirent.h>
# include	<fcntl.h>
# include	<sys/types.h>
# include	<signal.h>
# include	<limits.h>
# include	<termios.h>
# include	<dirent.h>
# include	<sys/stat.h>
# include	<sys/ioctl.h>
# include	<sys/param.h>
# include	<readline/readline.h>
# include	<readline/history.h>

# define R 0
# define W 1

typedef struct s_mini
{
	// Incializamos desde el main
	char **envp;
	char *pwd;
}	t_mini;

void	ft_mini_header(void);
void	ft_set_values(t_mini *mini, char **envp);
char	*ft_find_in_envp(char *variable, char** envp);
char	*ft_remove_varible(char *dst, const char *var_content);

#endif