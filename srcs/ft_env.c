/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**make_key_list2(t_env *env_list)
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

static	void	print_and_free2(char **env_key_list)
{
	char	**tmp;
	char	**tmp2;

	tmp = env_key_list;
	while (*tmp)
	{
		if (my_strcmp(get_env_value(*tmp), "") != 0)
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

static	void	print_sort_list2(t_env *env_list)
{
	char	**key_list;

	key_list = make_key_list2(env_list);
	print_and_free2(key_list);
}

int	ft_env(t_cmd *c_list, t_sh_data *g_data)
{
	set_pipe(c_list);
	set_rd(c_list->r_list);
	print_sort_list2(g_data->env_list);
	g_data->ret = 0;
	return (g_data->ret);
}
