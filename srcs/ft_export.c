/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exprot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_key_list(t_env *env_list, int *j)
{
	int		i;
	char	**tmp;
	t_env	*env_tmp;

	env_tmp = env_list;
	i = 0;
	while (env_tmp)
	{
		env_tmp = env_tmp->next;
		i++;
	}
	*j = i;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	tmp[i] = 0;
	i = 0;
	env_tmp = env_list;
	while (env_tmp)
	{
		tmp[i] = ft_strdup(env_tmp->key);
		env_tmp = env_tmp->next;
		i++;
	}
	return (tmp);
}

void	print_sort_list(t_env *env_list)
{
	char	**key_list;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	key_list = make_key_list(env_list, &k);
	j = 0;
	i = 0;
	while (i < k)
	{
		j = i + 1;
		while (j < k)
		{
			if (ft_strcmp(*(key_list + i), *(key_list + j)) > 0)
			{
				tmp = *(key_list + i);
				*(key_list + i) = *(key_list + j);
				*(key_list + j) = tmp;
			}
			j++;
		}
		i++;
	}
	print_and_free(key_list);
}

t_env	*make_env(char *key, char *value)
{
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
	tmp->prev = 0;
	tmp->next = 0;
	tmp->key = key;
	tmp->value = value;
	return (tmp);
}

int	input_env(t_env *env_list, char *argv)
{
	char	*value_index;
	char	*key_index;
	char	*tmp;

	value_index = ft_strchr(argv, '=');
	if (error_print(argv, value_index) == 1)
		return (1);
	if (value_index == 0 )
		check_delete_env(env_list, argv);
	else
	{
		key_index = (char *)malloc(value_index - argv + 1);
		tmp = value_index + 1;
		ft_strlcpy(key_index, argv, (value_index - argv) + 1);
		value_index = (char *)malloc(ft_strlen(tmp) + 1);
		ft_strlcpy(value_index, tmp, ft_strlen(tmp) + 1);
		delete_env(env_list, key_index);
		env_add_back(&env_list, make_env(key_index, value_index));
	}
	return (0);
}

void	ft_export(t_cmd *c_list, t_sh_data *g_data)
{
	int		size;
	bool	tf;
	t_list	*tmp;

	tf = false;
	set_pipe(c_list);
	set_rd(c_list->r_list);
	tmp = c_list->cmd->next;
	size = ft_lstsize(c_list->cmd);
	if (size == 1)
		print_sort_list(g_data->env_list);
	else
	{
		while (tmp)
		{
			if (input_env(g_data->env_list, tmp->content) == 1)
				tf = true;
			tmp = tmp->next;
		}
	}
	if (tf)
		g_data->status = 1;
}
