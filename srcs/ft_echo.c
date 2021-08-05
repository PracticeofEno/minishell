/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	print_echo(t_list *tmp, int flag)
{
	while (tmp)
	{
		write(1, tmp->content, ft_strlen(tmp->content));
		tmp = tmp->next;
		if (tmp)
			write(1, " ", 1);
	}
	if (flag)
		write(1, "\n", 1);
}

int	ft_echo(t_cmd *c_list)
{
	int		flag;
	int		size;
	t_list	*tmp;

	g_data->ret = 0;
	set_pipe(c_list);
	set_rd(c_list->r_list);
	tmp = c_list->cmd->next;
	size = ft_lstsize(c_list->cmd);
	flag = 1;
	if (size == 1)
		return (g_data->ret);
	else if ((my_strcmp(tmp->content, "-n") == 0))
	{
		if (size == 2)
			return (g_data->ret);
		tmp = tmp->next;
		flag = 0;
	}
	print_echo(tmp, flag);
	close(c_list->fds[1]);
	return (g_data->ret);
}
