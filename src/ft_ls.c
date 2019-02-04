/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 15:09:37 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/14 16:17:41 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				create_directory(char *arg, unsigned int flags, t_list **dlst)
{
	DIR				*dir;
	struct dirent	*el;

	if ((dir = opendir(arg)) == NULL)
	{
		b_printf("ft_ls: %s: Permission denied:", arg);
		return (-1);
	}
	while ((el = readdir(dir)) != NULL)
	{
		if (!(is_flag(flags, 'a')) && ft_strncmp(el->d_name, ".", 1) == 0)
			continue;
		else
			ft_lstadd(dlst, ft_lstnew(el->d_name, sizeof(char*), arg));
	}
	closedir(dir);
	return (0);
}

void			print_directory(t_list *dlst, t_list *slst, unsigned int flags)
{
	t_list	*cpy;

	cpy = dlst;
	while (cpy != NULL)
	{
		print_node(cpy, flags);
		b_printf("\n");
		cpy = cpy->next;
	}
	if (is_flag(flags, 'R'))
		print_recur(dlst, slst, flags);
}

void			is_direc(t_list *slst, unsigned int flags, int total)
{
	char	*tmp;
	t_list	*ptr;

	ptr = NULL;
	tmp = ft_strjoin(slst->content_path, slst->content);
	create_directory(tmp, flags, &ptr);
	free(tmp);
	sort_list(&ptr, flags);
	if (ptr != NULL)
		print_details(ptr, flags, total);
	else
	{
		tmp = ft_strjoin(slst->content_path, slst->content);
		b_printf("%s\n", tmp);
		free(tmp);
	}
	print_directory(ptr, slst, flags);
	ft_lstdel(&ptr, ft_nodedel);
}

void			sort_lists(t_list *slst, t_list *ilst, unsigned int flags,
				int total)
{
	t_list	*ptr;

	if (slst == NULL && ilst == NULL)
		ft_lstadd(&slst, ft_lstnew(".", sizeof(char*), "."));
	sort_list(&slst, flags);
	sort_list(&ilst, 0);
	ptr = ilst;
	while (ptr != NULL)
	{
		b_printf("ft_ls: %s: No such file or directory\n", ptr->content);
		ptr = ptr->next;
	}
	ft_lstdel(&ilst, ft_nodedel);
	ptr = slst;
	sort_and_print(ptr, flags, total);
	ft_lstdel(&slst, ft_nodedel);
}

int				create_lists(char **argv, unsigned int flags)
{
	int		total;
	t_list	*slst;
	t_list	*ilst;

	total = 0;
	slst = NULL;
	ilst = NULL;
	while (argv[total])
	{
		if (d_or_f("", argv[total]) == '\0')
			ft_lstadd(&ilst, ft_lstnew(argv[total++], sizeof(char*), "."));
		else
		{
			if (ft_strncmp(argv[total], "/", 1) == 0)
				ft_lstadd(&slst, ft_lstnew(argv[total++], sizeof(char*), ""));
			else
				ft_lstadd(&slst, ft_lstnew(argv[total++], sizeof(char*), "."));
		}
	}
	sort_lists(slst, ilst, flags, total);
	return (0);
}
