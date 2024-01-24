/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:04:56 by dan               #+#    #+#             */
/*   Updated: 2024/01/24 08:50:09 by dan              ###   ########.fr       */
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

	data = (t_Data *)malloc(sizeof(t_Data));
	if (!(data->envp = duplicate_envp(data, envp)))
		return (display_error("Error\n"), free_data(data), 255);
	rl_catch_signals = 0;
	if (data == NULL)
		return (display_error("Error\n"), free_data(data), 255);
	if (argc != 1)
		return (free_data(data), display_error("Usage: ./minishell\n"), 255);
	handle_signals();
	if (prompt_loop(data, envp) == 0)
		return (free_data(data), 255);
	return (0);
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
		if (command_is_builtin(command, data) == 0)
			return (free(command), close_minishell(data), 1);
		free(command);
	}
	return (1);
}

/**========================================================================
 *                           command_is_builtin
 * exit builtin implemented without extern function
 * 0 is returned, and the data struct is freed in calling function
 *========================================================================**/
int	command_is_builtin(char *command, t_Data *data)
{
	char	**command_tab;

	command_tab = ft_split(command, ' ');
	if (!command_tab)
		return (1);
	if (!command_tab[0])
		return (free(command_tab), 1);
	if (!ft_strncmp(command_tab[0], "echo", 5))
		exec_echo(command_tab);
	if (!ft_strncmp(command_tab[0], "unset", 6))
		exec_unset(data->envp, command_tab);
	if (!ft_strncmp(command_tab[0], "env", 4))
		exec_env(data->envp, command_tab);
	if (!ft_strncmp(command_tab[0], "pwd", 4))
		exec_pwd();
	if (!ft_strncmp(command_tab[0], "cd", 3))
		exec_cd(command_tab);
	if (!ft_strncmp(command_tab[0], "exit", 5))
		return (free_command_tab(command_tab), ft_printf("exit\n"), 0);
	free_command_tab(command_tab);
	return (1);
}

char	**duplicate_envp(t_Data *data, char *envp[])
{
	char	**envp_tab;
	int		i;
	
	i = 0;
	while (envp[i])
		i++;
	envp_tab = (char **)malloc(sizeof(char *) * i + 1);
	if (envp_tab == NULL)
		return (NULL);
	envp_tab[i] = NULL;
	while (--i >= 0)
		envp_tab[i] = envp[i];	
	return (envp_tab);
}

