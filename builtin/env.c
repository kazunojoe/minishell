/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:08:17 by jhii              #+#    #+#             */
/*   Updated: 2022/06/17 16:22:58 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	check_env(char *str)
{
	if (ft_strlen(str) != 3)
		return (0);
	if (str[0] != 'e' && str[0] != 'E')
		return (0);
	if (str[1] != 'n' && str[1] != 'N')
		return (0);
	if (str[2] != 'v' && str[2] != 'V')
		return (0);
	return (1);
}

static	void	print_msg(t_array *array, int j)
{
	if (array->cd_count > 0)
		printf("%s=%s\n", array->env.key[j],
			array->env.value[j]);
}

static	void	print_error(t_array *array, int prc)
{
	array->exitstat = 127;
	printf("env: %s: No such file or directory\n",
		array->cmd_group[prc].args[0]);
}

int	print_env(t_array *array, int prc)
{
	int	j;

	if (!array->cmd_group[prc].cmd)
		return (0);
	if (check_env(array->cmd_group[prc].cmd))
	{
		if (array->cmd_group[prc].n_arg == 0)
		{
			j = 0;
			while (j < array->env.size)
			{
				if (ft_strcmp(array->env.key[j], "OLDPWD"))
					print_msg(array, j);
				else
					printf("%s=%s\n", array->env.key[j], array->env.value[j]);
				j++;
			}
			array->exitstat = 0;
		}
		else
			print_error(array, prc);
		return (1);
	}
	return (0);
}
