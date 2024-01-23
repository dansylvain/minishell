/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:04:56 by dan               #+#    #+#             */
/*   Updated: 2024/01/23 16:12:57 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**========================================================================
 *                           main.c
 *? rl_catch_signals is a global variable (from readline lib)
 *? it is used to ignore SIGQUILL (see handle_signals.c)
*========================================================================**/
int	main(int argc, char **argv, char *envp[])
{
	t_Data	*data;

	rl_catch_signals = 0;
	data = (t_Data *)malloc(sizeof(t_Data));
	if (data == NULL)
		return (display_error("Error\n"), 255);
	if (argc != 1)
		return (free_data(data), display_error("Usage: ./minishell\n"), 255);
	handle_signals();
	if (prompt_loop(data, envp) == 0)
		return (free_data(data), 255);
	return (0);
}

void	free_command_tab(char **command_tab)
{
	int	i;

	i = 0;
	while (command_tab[i])
		free(command_tab[i++]);
	free(command_tab);
}

/**========================================================================
 *                           command_is_builtin
 * exit builtin implemented without extern function
 * 0 is returned, and the data struct is freed in calling function
 *========================================================================**/
int	command_is_builtin(char *command, char *envp[])
{
	char	**command_tab;

	command_tab = ft_split(command, ' ');
	if (!ft_strncmp(command_tab[0], "env", 4))
		exec_env(envp, command_tab);
	if (!ft_strncmp(command_tab[0], "pwd", 4))
		exec_pwd();
	if (!ft_strncmp(command_tab[0], "exit", 5))
		return (ft_printf("exit\n"), 0);
	if (!ft_strncmp(command_tab[0], "cd", 3))
		exec_cd(command_tab);
	free_command_tab(command_tab);
	return (1);
}

/**========================================================================
 *                           
 * possibility to add the path before prompt with this function
 * (write a function "build_prompt")
 * prompt = getcwd(NULL, 0);
 *========================================================================**/
int	prompt_loop(t_Data *data, char *envp[])
{
	char	*command;
	char	*prompt;

	while (1)
	{
		command = readline("minishell> ");
		if (command && *command)
		{
			add_history(command);
		}
		if (command == NULL)
			return (close_minishell(data), 1);
		if (command_is_builtin(command, envp) == 0)
			return (0);
		free(command);
	}
	return (1);
}
