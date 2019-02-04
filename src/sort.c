/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:53:02 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/14 11:38:31 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				should_switch(t_list *ptr1, t_list *ptr2, unsigned int flags)
{
	struct stat	buf1;
	struct stat	buf2;
	char		*tmp;

	tmp = ft_strjoin(ptr1->content_path, ptr1->content);
	lstat(tmp, &buf1);
	free(tmp);
	tmp = ft_strjoin(ptr2->content_path, ptr2->content);
	lstat(tmp, &buf2);
	free(tmp);
	if ((!is_flag(flags, 'r') && !is_flag(flags, 't')
		&& ft_strcmp(ptr1->content, ptr2->content) > 0)
		|| (is_flag(flags, 'r') && !is_flag(flags, 't')
		&& ft_strcmp(ptr1->content, ptr2->content) < 0)
		|| (is_flag(flags, 't') && !is_flag(flags, 'r')
		&& (buf1.st_mtimespec.tv_sec < buf2.st_mtimespec.tv_sec))
		|| (is_flag(flags, 't') && is_flag(flags, 'r')
		&& buf1.st_mtimespec.tv_sec > buf2.st_mtimespec.tv_sec))
		return (1);
	return (0);
}

t_list			*merge_sorted(t_list *a, t_list *b, unsigned int flags)
{
	t_list	*result;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	result = NULL;
	if (should_switch(a, b, flags))
	{
		result = b;
		result->next = merge_sorted(a, b->next, flags);
	}
	else
	{
		result = a;
		result->next = merge_sorted(a->next, b, flags);
	}
	return (result);
}

void			split(t_list *list, t_list **a, t_list **b)
{
	t_list	*back;
	t_list	*end;

	if (list == NULL || list->next == NULL)
	{
		*a = list;
		*b = NULL;
		return ;
	}
	back = list;
	end = list->next;
	while (end != NULL)
	{
		end = end->next;
		if (end != NULL)
		{
			back = back->next;
			end = end->next;
		}
	}
	*a = list;
	*b = back->next;
	back->next = NULL;
}

void			sort_list(t_list **list, unsigned int flags)
{
	t_list	*a;
	t_list	*b;

	if (*list == NULL || (*list)->next == NULL)
		return ;
	split(*list, &a, &b);
	sort_list(&a, flags);
	sort_list(&b, flags);
	*list = merge_sorted(a, b, flags);
}
