/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_strcmp(char *a, char *b)
{
	int	size_a;
	int	size_b;

	size_a = ft_strlen(a);
	size_b = ft_strlen(b);
	if (size_a != size_b)
		return (-1);
	return (ft_strcmp(a, b));
}

char	*get_env_value(char *key)
{
	t_env	*tmp;

	tmp = g_data->env_list;
	while (tmp)
	{
		if (my_strcmp(key, tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return ((void *)0);
}

t_env	*env_last(t_env *lst)
{
	t_env	*tmp;
	t_env	*tmp2;

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

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if ((*lst) == NULL)
	{
		*lst = new;
	}
	else
	{
		last = env_last(*lst);
		last->next = new;
		new->prev = last;
	}
}

t_env	*parse_env(char **envp)
{
	t_env	*env_list;
	t_env	*tmp;
	char	**splits;

	env_list = 0;
	while (*envp)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		splits = ft_split(*envp, '=');
		tmp->key = splits[0];
		tmp->value = splits[1];
		tmp->prev = 0;
		tmp->next = 0;
		env_add_back(&env_list, tmp);
		envp++;
	}
	return (env_list);
}
