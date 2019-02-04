/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:51:31 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/14 14:50:35 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				is_flag(unsigned int flags, char arg)
{
	if (arg == 'a')
		return (flags & 00000001);
	if (arg == 'l')
		return (flags & 00000010);
	if (arg == 'r')
		return (flags & 00000100);
	if (arg == 't')
		return (flags & 00001000);
	if (arg == 'R')
		return (flags & 00010000);
	return (-1);
}

unsigned int	add_flag(unsigned int flags, char arg)
{
	if (arg == 'a')
		return (flags | 00000001);
	if (arg == 'l')
		return (flags | 00000010);
	if (arg == 'r')
		return (flags | 00000100);
	if (arg == 't')
		return (flags | 00001000);
	if (arg == 'R')
		return (flags | 00010000);
	b_printf("ls: illegal option -- %c\nusage: b_ls [-alrtR] [file ...]", arg);
	return (0);
}

char			file_type(mode_t mode)
{
	char c;

	c = '\0';
	if ((mode & S_IFMT) == S_IFIFO)
		c = 'p';
	else if ((mode & S_IFMT) == S_IFCHR)
		c = 'c';
	else if ((mode & S_IFMT) == S_IFDIR)
		c = 'd';
	else if ((mode & S_IFMT) == S_IFBLK)
		c = 'b';
	else if ((mode & S_IFMT) == S_IFREG)
		c = '-';
	else if ((mode & S_IFMT) == S_IFLNK)
		c = 'l';
	else if ((mode & S_IFMT) == S_IFSOCK)
		c = 's';
	return (c);
}

char			*get_mode(mode_t mode)
{
	char *md;

	md = malloc(sizeof(char) * 11);
	md[0] = file_type(mode);
	md[1] = (mode & S_IRUSR) ? 'r' : '-';
	md[2] = (mode & S_IWUSR) ? 'w' : '-';
	md[3] = (mode & S_IXUSR) ? 'x' : '-';
	md[4] = (mode & S_IRGRP) ? 'r' : '-';
	md[5] = (mode & S_IWGRP) ? 'w' : '-';
	md[6] = (mode & S_IXGRP) ? 'x' : '-';
	md[7] = (mode & S_IROTH) ? 'r' : '-';
	md[8] = (mode & S_IWOTH) ? 'w' : '-';
	md[9] = (mode & S_IXOTH) ? 'x' : '-';
	(!(mode & S_IXUSR) && (mode & S_ISUID)) ? (md[3] = 'S') : (0);
	((mode & S_IXUSR) && (mode & S_ISUID)) ? (md[3] = 's') : (0);
	(!(mode & S_IXGRP) && (mode & S_ISGID)) ? (md[6] = 'S') : (0);
	((mode & S_IXGRP) && (mode & S_ISGID)) ? (md[6] = 's') : (0);
	(!(mode & S_IXOTH) && (mode & S_ISVTX)) ? (md[9] = 'T') : (0);
	((mode & S_IXOTH) && (mode & S_ISVTX)) ? (md[9] = 't') : (0);
	md[10] = '\0';
	return (md);
}

char			d_or_f(char *a, char *b)
{
	struct stat	buf;
	char		*tmp;

	tmp = ft_strjoin(a, b);
	lstat(tmp, &buf);
	free(tmp);
	return (file_type(buf.st_mode));
}
