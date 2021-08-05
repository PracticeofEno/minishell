/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **commands)
{
	int		size;
	char	tmp[1000];
	int		i;
	char	*tmp2;

	i = 0;
	tmp2 = *commands;
	size = get_env_len(*commands);
	if (size == 1 && *(tmp2) == '$')
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
	{
		return (0);
			
	}
	return (get_env_value(tmp));
}

int	calc_malloc_count(char *commands)
{
	int	count;

	count = 0;
	while (*commands)
	{
		if (*commands == '"')
			count = count + count_double_quotes(&commands);
		else if (*commands == '$')
			count = count + count_env(&commands);
		else if (*commands == '\'')
			count = count + count_one_quotes(&commands);
		else
		{
			commands++;
			count++;
		}
	}
	return (count);
}

void	cmd_lstiter(t_list *lst)
{
	t_list	*tmp;
	char	*tmp2;

	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->content;
		tmp->content = convert_quotes(tmp->content);
		free(tmp2);
		tmp = tmp->next;
	}
}

char	*convert_quotes(char *commands)
{
	char	*env_value;
	char	*tmp;
	char	*tmp2;
	int		malloc_count;

	malloc_count = calc_malloc_count(commands);
	tmp = (char *)malloc(malloc_count + 1);
	tmp[malloc_count] = 0;
	tmp2 = tmp;
	while (*commands)
	{
		if (*commands == '"')
			convert_double_quotes(&tmp, &commands);
		else if (*commands == '$')
		{
			env_value = get_env(&commands);
			ft_strlcpy(tmp, env_value, ft_strlen(env_value) + 1);
			tmp = tmp + ft_strlen(env_value);
		}
		else if (*commands == '\'')
			convert_one_quotes(&tmp, &commands);
		else
			*tmp++ = *commands++;
	}
	return (tmp2);
}

void	reset_buf(char *k)
{
	int	i;

	if (k == 0)
		return ;
	i = 0;
	while (i < 9000)
	{
		k[i] = 0;
		i++;
	}
}
