/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_free_rd(t_list *tmp)
{
	t_list	*pre_tmp;
	t_list	*next_tmp;
	t_list	*tmp2;

	pre_tmp = 0;
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->content, ">") == 0
			|| ft_strcmp((char *)tmp->content, "<") == 0
			|| ft_strcmp((char *)tmp->content, ">>") == 0)
		{
			tmp2 = tmp->next->next;
			if (pre_tmp)
				pre_tmp->next = tmp2;
			next_tmp = tmp->next;
			free_rd(tmp);
			free_rd(next_tmp);
			tmp = tmp2;
		}
		else
		{
			pre_tmp = tmp;
			tmp = tmp->next;
		}
	}
}

bool	check_filename_valid(char *str)
{
	char	tmp[3];

	tmp[0] = '\\';
	tmp[1] = 'n';
	tmp[2] = 0;
	if (my_strcmp(str, "|") == 0 || my_strcmp(str, "<") == 0
		|| my_strcmp(str, ">") == 0 || my_strcmp(str, ">>") == 0
		|| my_strcmp(str, ";") == 0 || my_strcmp(str, tmp) == 0
		|| my_strcmp(str, "<<") == 0)
	{
		if (my_strcmp(str, tmp) == 0)
			printf("parse error near by '\\n'\n");
		else
			printf("parse error near by '%s'\n", str);
		return (false);
	}
	return (true);
}

bool	check_redirect_parse(t_list *tmp)
{
	t_list	*tmp2;
	char	*c;
	char	*d;

	tmp2 = tmp;
	while (tmp2)
	{
		c = (char *)tmp2->content;
		if (my_strcmp(c, ">") == 0 || my_strcmp(c, "<") == 0
			|| my_strcmp(c, ">>") == 0 || my_strcmp(c, "<<") == 0)
		{
			if (tmp2->next)
				d = (char *)tmp2->next->content;
			else
			{
				printf("parse error near by '%s'\n", c);
				return (false);
			}
			if (check_filename_valid(d) == false)
				return (false);
		}
		tmp2 = tmp2->next;
	}
	return (true);
}

bool	make_redirection_list(t_list *tmp, t_rd **r_list)
{
	t_list	*tmp2;
	char	*c;
	char	*d;

	tmp2 = tmp;
	while (tmp2)
	{
		c = (char *)tmp2->content;
		if (ft_strcmp(c, ">") == 0 || ft_strcmp(c, "<") == 0
			|| ft_strcmp(c, ">>") == 0)
		{
			d = (char *)tmp2->next->content;
			rd_lstadd_back(r_list, rd_lstnew(c, d));
		}
		tmp2 = tmp2->next;
	}
	return (true);
}

int	check_parse_error(char *commands)
{
	t_list	*tmp;

	tmp = make_token_list(commands);
	if (check_redirect_parse(tmp) == false)
	{
		free_list(tmp);
		return (-1);
	}
	free_list(tmp);
	return (1);
}
