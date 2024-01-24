/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:08:19 by dan               #+#    #+#             */
/*   Updated: 2024/01/24 10:43:12 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_swap(char *var)
{

}

void	exec_export(char **command_tab, t_Data *data)
{
	int i;
	char *temp;

	i = 0;
	while (data->envp[i] && data->envp[i + 1])
	{
		if (ft_strncmp(data->envp[i], data->envp[i + 1], ft_strlen(data->envp[i])) > 0)
		{
			temp = data->envp[i];
			data->envp[i] = data->envp[i + 1];
			data->envp[i + 1] = temp;
			i = 0;
		}
		i++;
	}
	i = 0;
	if (command_tab[1] == NULL)
	{
		while (data->envp[i])
			ft_printf("declare -x %s\n", data->envp[i++]);
	}
}