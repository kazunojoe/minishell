/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:31:32 by jhii              #+#    #+#             */
/*   Updated: 2022/06/17 16:22:01 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// update array->pwd && array->old_pwd && env
int	cd_path(t_array *array, int prc)
{
	if (!array->cmd_group[prc].cmd)
		return (0);
	if (ft_strcmp(array->cmd_group[prc].cmd, "cd"))
	{
		array->cd_count++;
		if (array->old_pwd)
			free(array->old_pwd);
		array->old_pwd = ft_strdup(array->pwd);
		return (1);
	}
	return (0);
}
