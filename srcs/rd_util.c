/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_need_fork(t_cmd *c_list)
{
	char	*tmp;

	tmp = c_list->cmd->content;
	if (my_strcmp(tmp, "echo") == 0 || my_strcmp(tmp, "env") == 0
		|| my_strcmp(tmp, "pwd") == 0)
	{
		return (1);
	}
	return (0);
}

int	check_none_fork(t_cmd *c_list)
{
	char	*tmp;

	tmp = c_list->cmd->content;
	if (my_strcmp(tmp, "cd") == 0 || my_strcmp(tmp, "export") == 0
		|| my_strcmp(tmp, "unset") == 0 || my_strcmp(tmp, "exit") == 0)
	{
		return (1);
	}
	return (0);
}

static	void	norm(t_rd *tmp, int *fd)
{
	while (tmp)
	{
		if (ft_strcmp(tmp->specific, ">>") == 0)
		{
			*fd = open(tmp->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
			dup2(*fd, g_data->stdout);
		}
		else if (*(tmp->specific) == '>')
		{
			*fd = open(tmp->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			dup2(*fd, g_data->stdout);
		}
		tmp = tmp->next;
	}
}

void	set_rd(t_rd *r_list)
{
	int		fd;
	t_rd	*tmp;

	tmp = r_list;
	norm(tmp, &fd);
	while (r_list)
	{
		if (ft_strcmp(r_list->specific, "<<") == 0)
		{
			herodoc(r_list->filename, r_list->next);
			fd = open("tmp", O_RDONLY);
			g_data->herodoc_fd = fd;
			dup2(fd, g_data->stdin);
		}
		else if (*(r_list->specific) == '<')
		{
			fd = open(r_list->filename, O_RDONLY);
			dup2(fd, g_data->stdin);
		}
		r_list = r_list->next;
	}
}

int	check_redirection_list(t_rd *r_list)
{
	int	fd;

	while (r_list)
	{
		if (my_strcmp(r_list->specific, "<<") == 0)
		{
			r_list = r_list->next;
			continue ;
		}
		else if (ft_strcmp(r_list->specific, ">>") == 0)
			fd = open(r_list->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (*(r_list->specific) == '>')
			fd = open(r_list->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (my_strcmp(r_list->specific, "<") == 0)
			fd = open(r_list->filename, O_RDONLY);
		if (fd == -1)
		{
			printf("no such file or directory: %s\n", r_list->filename);
			return (-1);
		}
		r_list = r_list->next;
	}
	return (1);
}
