/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:53:58 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/14 16:17:49 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void			print_long(struct stat buf)
{
	char			*tmp;
	char			*tmp1;
	struct passwd	*id;
	struct group	*gp;

	id = getpwuid(buf.st_uid);
	gp = getgrgid(buf.st_gid);
	tmp = get_mode(buf.st_mode);
	b_printf("%s", tmp);
	free(tmp);
	b_printf("  %d  ", buf.st_nlink);
	b_printf("%s  %s", id->pw_name, gp->gr_name);
	b_printf("  %d           ", buf.st_size);
	tmp = ft_strdup(ctime(&buf.st_mtime));
	tmp1 = ft_strsub(tmp, 4, 12);
	b_printf("%s    ", tmp1);
	free(tmp1);
	free(tmp);
}

int				print_node(t_list *arg, unsigned int flags)
{
	struct stat		buf;
	char			sym[256];
	int				len;
	char			*tmp;

	tmp = ft_strjoin(arg->content_path, arg->content);
	lstat(tmp, &buf);
	free(tmp);
	if (is_flag(flags, 'l'))
		print_long(buf);
	b_printf("%s", arg->content);
	if (is_flag(flags, 'l') && file_type(buf.st_mode) == 'l')
	{
		tmp = ft_strjoin(arg->content_path, arg->content);
		len = readlink(tmp, sym, sizeof(sym));
		free(tmp);
		sym[len] = '\0';
		b_printf(" -> %s", sym);
	}
	return (0);
}

int				print_details(t_list *sorted_d, unsigned int flags, int tfiles)
{
	t_list			*ptr;
	struct stat		buf;
	int				total;
	char			*tmp;

	ptr = sorted_d;
	total = 0;
	if (tfiles > 1 || is_flag(flags, 'R'))
		b_printf("%s:\n", ptr->content_path);
	if (is_flag(flags, 'l'))
	{
		while (ptr != NULL)
		{
			tmp = ft_strjoin(ptr->content_path, ptr->content);
			lstat(tmp, &buf);
			free(tmp);
			total += buf.st_blocks;
			ptr = ptr->next;
		}
		b_printf("total %i\n", total);
	}
	return (0);
}

void			print_recur(t_list *cpy, t_list *slst, unsigned int flags)
{
	t_list	*rec;
	char	*tmp;

	rec = NULL;
	while (cpy != NULL)
	{
		if (ft_strncmp(cpy->content, ".", 2) != 0 &&
			(ft_strncmp(cpy->content, ".", 1) != 0 ||
			ft_strlen(cpy->content) > 2) &&
			d_or_f(cpy->content_path, cpy->content) == 'd')
		{
			tmp = ft_strjoin(slst->content_path, slst->content);
			ft_lstadd(&rec, ft_lstnew(cpy->content, sizeof(char*), tmp));
			free(tmp);
		}
		cpy = cpy->next;
	}
	if (rec != NULL)
	{
		sort_list(&rec, flags);
		sort_and_print(rec, flags, 1);
		ft_lstdel(&rec, ft_nodedel);
	}
}

int				sort_and_print(t_list *slst, unsigned int flags, int total)
{
	while (slst != NULL)
	{
		if (d_or_f("", slst->content) == '-')
			print_node(slst, flags);
		else
			is_direc(slst, flags, total);
		b_printf("\n");
		slst = slst->next;
	}
	return (0);
}
