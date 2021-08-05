/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_relpace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:24:37 by sanghpar          #+#    #+#             */
/*   Updated: 2020/10/05 00:09:30 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_same_count(char *str, char *src)
{
	char	*tmp;
	int		count;

	count = 0;
	tmp = str;
	while (true)
	{
		tmp = ft_strstr(tmp, src);
		if (tmp == 0)
			break ;
		else
		{
			count++;
			tmp++;
		}
	}
	return (count);
}

// *str is must malloc pointer 
// when ft_strstr is not null free(*str) -> *str = ret
void	ft_replace(char **str, char *src, char *dest)
{
	char	*tmp;
	char	*ret;
	int		i;
	int		size;

	size = (ft_strlen(*str) + (-ft_strlen(src) + ft_strlen(dest))
			* get_same_count(*str, src));
	ret = (char *)malloc(size + 1);
	tmp = *str;
	i = 0;
	while (i < size)
	{
		if (ft_strcmp(tmp, src) != 0)
			ret[i++] = *tmp++;
		else
		{
			ft_strlcpy((ret + i), dest, ft_strlen(dest) + 1);
			i = i + ft_strlen(dest);
			tmp = tmp + ft_strlen(src);
		}
	}
	free(*str);
	*str = ret;
}
