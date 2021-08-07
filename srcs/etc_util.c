/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_cmd *c_list)
{
	if (g_data->ret == 126)
		printf("%s: is a directory\n", c_list->cmd->content);
	else if (g_data->ret == 127)
		printf("%s: command not found\n", c_list->cmd->content);
	else if (g_data->ret == 999)
	{
		printf("permission denined: %s\n", c_list->cmd->content);
		g_data->ret = 126;
	}
}

bool	check_current_folder(t_cmd *c_list)
{
	char		buf[5000];
	int			i;

	getcwd(buf, 5000);
	i = ft_strlen(buf);
	buf[i] = '/';
	ft_strlcpy((buf + i), c_list->cmd->content,
		ft_strlen(c_list->cmd->content) + 1);
	if (check_executable(buf, c_list) == 0)
	{
		execute_etc(c_list, buf);
		return (true);
	}
	return (false);
}

static	void	norm(int *i, char **paths, char *buf, t_cmd *c_list)
{
	*i = ft_strlen(*paths);
	ft_strlcpy(buf, *paths, ft_strlen(*paths) + 1);
	buf[*i] = '/';
	ft_strlcpy((buf + *i + 1), c_list->cmd->content,
		ft_strlen(c_list->cmd->content) + 1);
}

void	fork_execute3(t_cmd *c_list, char *buf)
{
	pid_t	pid;

	g_data->forked = 1;
	pid = fork();
	g_data->last_pid = pid;
	c_list->pid = pid;
	g_data->count = g_data->count + 1;
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		exit(execute_etc(c_list, buf));
	}
	else
	{
		close(c_list->fds[1]);
	}
}

bool	check_path_folder(t_cmd *c_list)
{
	int			i;
	char		buf[5000];
	char		*path_value;
	char		**paths;
	char		**tmp_paths;

	tmp_paths = 0;
	path_value = get_env_value("PATH");
	if (path_value)
	{
		paths = ft_split(path_value, ':');
		tmp_paths = paths;
		while (*paths)
		{
			norm(&i, paths, buf, c_list);
			if (check_executable(buf, c_list) == 0)
			{
				free_split(tmp_paths);
				fork_execute3(c_list, buf);
				return (true);
			}
			paths++;
		}
	}
	free_split(tmp_paths);
	return (false);
}
