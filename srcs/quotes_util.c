/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_double_quotes(char **commands)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = *commands;
	tmp++;
	while (*tmp)
	{
		if (*tmp == '"')
			break ;
		else if (*tmp == '$')
			count = count + count_env(&tmp);
		else
		{
			count++;
			tmp++;
		}
	}
	*commands = tmp + 1;
	return (count);
}

int	count_one_quotes(char **commands)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = *commands;
	tmp++;
	while (*tmp)
	{
		if (*tmp == '\'')
			break ;
		count++;
		tmp++;
	}
	*commands = tmp + 1;
	return (count);
}

void	convert_double_quotes(char **start, char **commands)
{
	char	*tmp;
	char	*env_value;
	int		i;

	tmp = *commands;
	tmp = tmp + 1;
	i = 0;
	while (*tmp)
	{
		if (*tmp == '"')
			break ;
		else if (*tmp == '$')
		{
			env_value = get_env2(&tmp, &i);
			ft_strlcpy(*start, env_value, ft_strlen(env_value) + 1);
			*start = *start + ft_strlen(env_value);
		}
		else
		{
			**start = *tmp;
			*start = *start + 1;
			tmp++;
		}
	}
	*commands = (++tmp);
}

void	convert_one_quotes(char **start, char **commands)
{
	char	*tmp;

	tmp = *commands;
	tmp++;
	while (*tmp)
	{
		if (*tmp == '\'')
			break ;
		**start = *tmp;
		*start = (*start) + 1;
		tmp++;
	}
	*commands = tmp + 1;
	return ;
}

int	count_env(char **commands)
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
		return (1);
	}
	tmp2++;
	while (i < size)
	{
		tmp[i] = *tmp2++;
		i++;
	}
	tmp[i] = 0;
	*commands = tmp2;
	if (get_env_value(tmp) == 0)
		return (0);
	else
		return (ft_strlen(get_env_value(tmp)));
}
