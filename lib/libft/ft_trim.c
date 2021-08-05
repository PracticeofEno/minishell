/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:24:37 by sanghpar          #+#    #+#             */
/*   Updated: 2020/10/05 00:09:30 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_left(char *s, char c)
{
	int		i;
	char	*tmp;

	tmp = s;
	i = 0;
	while (*tmp)
	{
		if (*tmp != c)
			break ;
		i++;
		tmp++;
	}
	return (i);
}

static int	get_right(char *s, char c)
{
	int		i;
	char	*tmp;
	int		count;

	i = ft_strlen(s);
	i--;
	count = 0;
	tmp = s;
	while (*(tmp + i))
	{
		if (i == 0)
			break ;
		if (*(tmp + i) != c)
			break ;
		count++;
		i--;
	}
	return (count);
}

// delete 'c' left right, and free str
char	*ft_trim(char *str, char c)
{
	char	*tmp;
	int		left;
	int		right;
	int		size;
	int		i;

	i = 0;
	if (str == 0)
		return ((void *)0);
	left = get_left(str, c);
	right = get_right(str, c);
	size = ft_strlen(str) - left - right;
	tmp = (char *)malloc(size + 1);
	while (i < size)
	{
		tmp[i] = str[left + i];
		i++;
	}
	tmp[i] = 0;
	free(str);
	return (tmp);
}
