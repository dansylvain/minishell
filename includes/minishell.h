/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:59:03 by dan               #+#    #+#             */
/*   Updated: 2024/01/23 15:59:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

void	handle_signals(void);
int		prompt_loop(t_Data *data, char *envp[]);
void	display_error(char *str);
void	free_data(t_Data *data);
void	close_minishell(t_Data *data);
void	exec_env(char *envp[]);
int		command_is_builtin(char *command, char *envp[]);
void	exec_pwd(void);
int		exec_cd(char **command_tab);

#endif