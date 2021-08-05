/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe(t_cmd *c_list)
{
	dup2(g_data->origin_stdin, 0);
	dup2(g_data->origin_stdout, 1);
	if (c_list->prev)
		dup2(c_list->prev->fds[0], 0);
	if (c_list->pipe)
		dup2(c_list->fds[1], 1);
}

int	none_fork_execute(t_cmd *c_list)
{
	char	*tmp;

	tmp = c_list->cmd->content;
	if (my_strcmp(tmp, "cd") == 0)
		ft_cd(c_list);
	else if (my_strcmp(tmp, "unset") == 0)
		ft_unset(c_list, g_data);
	else if (my_strcmp(tmp, "export") == 0)
		ft_export(c_list, g_data);
	else if (my_strcmp(tmp, "exit") == 0)
		ft_exit(c_list, g_data);
	return (0);
}

void	fork_execute(t_cmd *c_list)
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
		exit(child_execute(c_list));
	}
	else
	{
		close(c_list->fds[1]);
	}
}

void	close_fd_dup(t_cmd *c_list)
{
	(void)c_list;
	dup2(g_data->origin_stdin, g_data->stdin);
	dup2(g_data->origin_stdout, g_data->stdout);
	g_data->forked = 0;
}

void	execute(t_cmd *c_list)
{
	if (check_redirection_list(c_list->r_list) == -1)
		return ;
	if (check_need_fork(c_list) == 1)
		fork_execute(c_list);
	else if (check_none_fork(c_list) == 1)
		none_fork_execute(c_list);
	else
		etc(c_list);
	close_fd_dup(c_list);
}
