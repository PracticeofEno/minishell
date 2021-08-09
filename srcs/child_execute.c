/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_term(struct termios term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	rd_norm_pass(char *buf, char **command)
{
	*buf = **command;
	buf = buf + 1;
	*command = *command + 1;
}

int	child_execute(t_cmd *c_list)
{
	pid_t	pid;
	int		status;

	g_data->forked = 1;
	pid = fork();
	status = 0;
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		if (is_same(c_list->cmd->content, "pwd"))
			return (ft_pwd(c_list));
		else if (is_same(c_list->cmd->content, "env"))
			return (ft_env(c_list, g_data));
		else if (is_same(c_list->cmd->content, "echo"))
			return (ft_echo(c_list));
	}
	else
	{
		waitpid(pid, &status, 0);
		close(c_list->fds[1]);
	}
	return (status);
}

char	*get_env2(char **commands, int *j)
{
	int		size;
	char	tmp[1000];
	int		i;
	char	*tmp2;

	i = 0;
	tmp2 = *commands;
	size = get_env_len(*commands);
	*j = size;
	if (size == 0 && *tmp2 == '$')
	{
		*commands = *commands + 1;
		return (ft_strdup("$"));
	}
	tmp2++;
	while (i < size)
	{
		tmp[i] = *tmp2;
		tmp2++;
		i++;
	}
	tmp[i] = 0;
	*commands = tmp2;
	if (get_env_value(tmp) == 0)
		return (0);
	return (ft_strdup(get_env_value(tmp)));
}
