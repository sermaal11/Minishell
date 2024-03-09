/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/09 17:17:51 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Regular

# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define ORANGE "\033[0;91m"
# define PINK "\033[0;95m"

// Bold
# define BOLD_BLACK "\033[1;30m"
# define BOLD_RED "\033[1;31m"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_YELLOW "\033[1;33m"
# define BOLD_BLUE "\033[1;34m"
# define BOLD_PURPLE "\033[1;35m"
# define BOLD_CYAN "\033[1;36m"
# define BOLD_WHITE "\033[1;37m"
# define BOLD_ORANGE "\033[1;91m"
# define BOLD_PINK "\033[1;95m"

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

typedef struct s_quotes
{
	int		dou;
	int		sim;
	int		pipe;
	int		other;
	int		error;
	int		words;
	int		o_space;
}			t_quotes;

typedef struct s_mini
{
	// Incializamos desde el main
	t_quotes	*quotes;
	
	int			start;
	int			g_error;
	int			exit_status;
	
	char		*pwd;
	char		*input;
	char		*code_error;

	char		**envp;
}				t_mini;

int		ft_invalid_expr(t_mini *mini);

void	ft_mini_header(void);
void	ft_not_variable(void);
void	ft_initialize(t_mini *mini);
// void	ft_free_matrix(char **matrix);
void	ft_set_values(t_mini *mini, char** argv, char **envp);

char	*ft_find_in_envp(char *variable, char** envp);
char	*ft_remove_varible(char *dst, char *var_content);

char	**ft_mini_split(t_mini *mini, char *str);
char	**mini_split(t_mini *mini, char *str);

#endif