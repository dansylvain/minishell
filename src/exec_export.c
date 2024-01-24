/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:08:19 by dan               #+#    #+#             */
/*   Updated: 2024/01/24 11:53:53 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_export(char **command_tab, t_Data *data)
{
	int i;
	int j;
	int k;
	bool equal_was_done;
	char *temp;
	char envp_export_tab[100][500];

	i = 0;
	while (data->envp[++i])
		if (ft_strncmp(data->envp[i], "_=", 2) == 0)
			data->envp[i] = NULL;
	i = 0;
	while (data->envp[i] && data->envp[++i + 1])
		if (ft_strncmp(data->envp[i], data->envp[i + 1], ft_strlen(data->envp[i])) > 0)
		{
			temp = data->envp[i];
			data->envp[i] = data->envp[i + 1];
			data->envp[i + 1] = temp;
			i = -1;
		}
	i = 0;
	while (data->envp[i])
	{
		equal_was_done = 0;
		j = 0;
		k = 0;
		while (data->envp[i][j])
		{
			envp_export_tab[i][k] = data->envp[i][j];
			if (data->envp[i][j] == '=' && equal_was_done == 0)
			{
				k++;
				envp_export_tab[i][k] = '"';
				equal_was_done = 1;	
			}
			j++;
			k++;
		}
		envp_export_tab[i][k] = '"';
		i++;
	}
	i = 0;
	if (command_tab[1] == NULL)
		while (data->envp[i])
			ft_printf("declare -x %s\n", envp_export_tab[i++]);
}
