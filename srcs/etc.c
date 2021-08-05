/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**make_argv(t_cmd *c_list, char *buf)
{
	int		i;
	char	**tmp;
	t_list	*cmd;

	cmd = c_list->cmd->next;
	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	tmp[i + 1] = 0;
	i = 1;
	tmp[0] = ft_strdup(buf);
	cmd = c_list->cmd->next;
	while (cmd)
	{
		tmp[i] = ft_strdup(cmd->content);
		cmd = cmd->next;
		i++;
	}
	return (tmp);
}

int	execute_etc(t_cmd *c_list, char *buf)
{
	char	**argv;
	int		status;
	pid_t	pid;

	g_data->forked = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_data->child_term);
	pid = fork();
	if (pid == 0)
	{
		set_pipe(c_list);
		set_rd(c_list->r_list);
		argv = make_argv(c_list, buf);
		if (execve(buf, argv, g_data->envp) < 0)
			execute_ect2(c_list, argv);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_data->ret = WEXITSTATUS(status);
		close(c_list->fds[1]);
		tcsetattr(STDIN_FILENO, TCSANOW, &g_data->main_term);
		return (g_data->ret);
	}
	return (g_data->ret);
}

int	check_executable(char *buf, t_cmd *c_list)
{
	int			i;
	struct stat	sb;

	(void)c_list;
	i = stat(buf, &sb);
	if (i != 0)
	{
		g_data->ret = 127;
		return (1);
	}
	else if (S_ISDIR(sb.st_mode))
	{
		g_data->ret = 126;
		return (2);
	}
	else
	{
		if (sb.st_mode & S_IXUSR)
			return (0);
		else
		{
			g_data->ret = 999;
			return (3);
		}
	}
}

void	fork_execute2(t_cmd *c_list)
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
		exit(execute_etc(c_list, c_list->cmd->content));
	}
	else
	{
		close(c_list->fds[1]);
	}
}

void	etc(t_cmd *c_list)
{
	char	*cmd;

	cmd = c_list->cmd->content;
	if (*cmd != '/')
	{
		if (check_current_folder(c_list))
			return ;
		else if (check_path_folder(c_list))
			return ;
		else
			print_error(c_list);
	}
	else
	{
		if (check_executable(c_list->cmd->content, c_list) == 0)
			fork_execute2(c_list);
		else
			print_error(c_list);
	}
}
