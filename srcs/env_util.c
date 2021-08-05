/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_and_free(char **env_key_list)
{
	char	**tmp;
	char	**tmp2;

	tmp = env_key_list;
	while (*tmp)
	{
		printf("%s=\"%s\"\n", *tmp, get_env_value(*tmp));
		tmp++;
	}
	tmp2 = env_key_list;
	while (*tmp2)
	{
		tmp = tmp2 + 1;
		free(*tmp2);
		tmp2 = tmp;
	}
	free(env_key_list);
}

int	get_env_len(char *commands)
{
	char	*tmp;
	bool	start_number;
	int		count;

	count = 0;
	if (ft_isdigit(*commands) == 1)
		start_number = true;
	else
		start_number = false;
	tmp = commands;
	tmp++;
	if (*tmp == ' ' || *tmp == 0)
		return (1);
	while (*tmp)
	{
		if (!valid_env_name(*tmp, start_number))
			break ;
		count++;
		tmp++;
	}
	return (count);
}

// first character -> digit -> only digit
//            	   -> else -> digit, alpha, '_'
bool	valid_env_name(char c, bool start_number)
{
	if (start_number)
	{
		if (ft_isdigit(c) == 1)
			return (true);
		else
			return (false);
	}
	else
	{
		if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '_')
			return (true);
		else
			return (false);
	}
}
