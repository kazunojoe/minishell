/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:32:35 by jhii              #+#    #+#             */
/*   Updated: 2022/06/18 19:59:49 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	print_file_error(t_array *array, char *filename, int type)
{
	char	*res;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_strjoin("minishell: ", filename);
	temp2 = ft_strdup(": no such file or directory\n");
	temp3 = ft_strdup(": permission denied\n");
	if (type == 1)
	{
		res = ft_strjoin(temp1, temp2);
		ft_putstr_fd(res, 2);
	}
	if (type == 2)
	{
		res = ft_strjoin(temp1, temp3);
		ft_putstr_fd(res, 2);
	}
	free(temp1);
	free(temp2);
	free(temp3);
	free(res);
	array->exitstat = 127;
}

static	int	checkfd1(t_array *array, char *filename)
{
	int	fd;

	fd = -1;
	if (access(filename, F_OK) < 0)
		print_file_error(array, filename, 1);
	else if (access(filename, R_OK) < 0)
		print_file_error(array, filename, 2);
	else
		fd = 1;
	return (fd);
}

// type[1] = infile, type[2] = outfile
static	int	checkfd(t_array *array, char *filename, int type)
{
	int	fd;

	fd = -1;
	if (type == 1)
		fd = checkfd1(array, filename);
	else
	{
		if (access(filename, F_OK) < 0)
		{
			fd = open(filename, O_CREAT, 0644);
			close(fd);
			fd = 1;
		}
		else if (access(filename, W_OK) < 0)
			print_file_error(array, filename, 2);
		else
			fd = 1;
	}
	return (fd);
}

int	checkfiles(t_array *array, int prc)
{
	int	i;

	i = 0;
	while (i < array->cmd_group[prc].redir.size)
	{
		if (array->cmd_group[prc].redir.types[i] == INFILE)
		{
			if (checkfd(array, array->cmd_group[prc].redir.files[i], 1) < 0)
				return (-1);
		}
		else if (array->cmd_group[prc].redir.types[i] == TRUNC
			|| array->cmd_group[prc].redir.types[i] == APPEND)
		{
			if (checkfd(array, array->cmd_group[prc].redir.files[i], 2) < 0)
				return (-1);
		}
		i++;
	}
	return (1);
}
