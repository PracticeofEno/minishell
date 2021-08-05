/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghpar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:09 by sanghpar          #+#    #+#             */
/*   Updated: 2020/11/19 14:00:25 by sanghpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef enum e_range
{
	all,
	without_tail
}					t_range;

typedef struct s_lst
{
	char			*buff;
	struct s_lst	*next;
}					t_lst;

/*
** - gnl_util
*/

ssize_t				ft_strchr(char *str, char c);
t_lst				*ft_lstnew(void);
ssize_t				ft_lstlen(t_lst *lst);
void				ft_lstcpy(char *dst, t_lst *lst);
void				ft_strcpy(char *dst, char *src);

/*
** - gnl
*/

ssize_t				ft_lstfree(t_lst *lsthead, t_lst **lsttail, t_range range);
ssize_t				ft_lstinit(t_lst **lsthead, t_lst **lsttail);
ssize_t				ft_link(char **line, t_lst *lsthead, t_lst **lsttail);
ssize_t				ft_split(char **line, t_lst *lsthead, t_lst **lsttail);
int					get_next_line(int fd, char **line);

#endif
