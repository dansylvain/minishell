/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:09:58 by dan               #+#    #+#             */
/*   Updated: 2024/01/24 07:00:26 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_var(char *envp[], int i)
{
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

void	exec_unset(char *envp[], char **command_tab)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (command_tab[j])
		{
			if ((!ft_strncmp(command_tab[j], envp[i], ft_strlen
						(command_tab[j]))) && envp[i][ft_strlen
				(command_tab[j])] == '=')
			{
				unset_var(envp, i);
				exec_unset(envp, command_tab);
			}
			j++;
		}
		i++;
	}
}
