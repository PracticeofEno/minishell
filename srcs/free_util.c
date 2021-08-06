/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ect2(t_cmd *c_list, char **argv)
{
	printf("bash: %s: %s\n", c_list->cmd->content, strerror(errno));
	if (errno == 13)
		exit(126);
	else if (errno == 2)
		exit(127);
	free_split(argv);
}

void	free_split(char **splits)
{
	char	**tmp;

	tmp = splits;
	while (*splits)
	{
		free(*splits);
		splits++;
	}
	free(tmp);
}

void	free_list(t_list *tmp)
{
	t_list	*tmp2;

	tmp2 = tmp;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = tmp2;
	}
}

void	free_r_list(t_rd *tmp)
{
	t_rd	*tmp2;

	tmp2 = tmp;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->filename)
			free(tmp->filename);
		if (tmp->specific)
			free(tmp->specific);
		free(tmp);
		tmp = tmp2;
	}
}

void	free_cmd(t_cmd	*cmd)
{
	t_cmd	*tmp;

	delete_tmp();
	while (cmd)
	{
		tmp = cmd->next;
		close(cmd->fds[0]);
		close(cmd->fds[1]);
		if (cmd->r_list)
			free_r_list(cmd->r_list);
		if (cmd->origin)
			free(cmd->origin);
		if (cmd->cmd)
			free_list(cmd->cmd);
		free(cmd);
		cmd = tmp;
	}
}
