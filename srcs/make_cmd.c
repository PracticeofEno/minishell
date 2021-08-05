/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_lstlast(t_cmd *lst)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	if (lst == 0)
		return ((void *)0);
	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	return (tmp2);
}

void	cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if ((*lst) == NULL)
	{
		*lst = new;
	}
	else
	{
		tmp = cmd_lstlast(*lst);
		tmp->next = new;
		new->prev = tmp;
	}
}

void	convert_qeustion(t_list *lst)
{
	t_list	*tmp;
	char	*tmp2;

	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->content;
		if (my_strcmp(tmp2, "$?") == 0)
		{
			tmp->content = ft_itoa(g_data->ret);
			free(tmp2);
		}
		tmp = tmp->next;
	}
}

t_cmd	*make_cmd(char *command, int pip)
{
	t_cmd	*tmp;
	t_list	*tokens;
	t_rd	*r_list;
	t_list	*start;

	r_list = 0;
	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	command = ft_trim(command, ' ');
	tokens = make_token_list(command);
	tmp->origin = command;
	convert_qeustion(tokens);
	cmd_lstiter(tokens);
	make_redirection_list(tokens, &r_list);
	start = set_start(tokens);
	del_free_rd(tokens);
	tmp->pipe = pip;
	tmp->r_list = r_list;
	tmp->cmd = start;
	tmp->next = 0;
	tmp->prev = 0;
	pipe(tmp->fds);
	return (tmp);
}
