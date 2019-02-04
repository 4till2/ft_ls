/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:03:35 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/14 16:09:53 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <string.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

void			is_direc(t_list *slst, unsigned int flags, int total);
int				sort_and_print(t_list *slst, unsigned int flags, int total);
void			print_recur(t_list *cpy, t_list *slst, unsigned int flags);
int				create_lists(char **argv, unsigned int flags);
int				create_lists(char **argv, unsigned int flags);
void			insert_node(char *arg, t_list **list);
int				create_directory(char *arg, unsigned int flags,
				t_list **sorted_d);
int				sort_and_print(t_list *sortedlist,
				unsigned int flags, int total);
int				is_flag(unsigned int flags, char arg);
unsigned int	add_flag(unsigned int flags, char arg);
char			file_type(mode_t mode);
char			*get_mode(mode_t mode);
char			d_or_f(char *a, char *b);
int				print_node(t_list *arg, unsigned int flags);
int				print_details(t_list *sorted_d,
				unsigned int flags, int totalfiles);
int				should_switch(t_list *ptr1, t_list *ptr2, unsigned int flags);
t_list			*merge_sorted(t_list *a, t_list *b, unsigned int flags);
void			split(t_list *list, t_list **a, t_list **b);
void			sort_list(t_list **list, unsigned int flags);
#endif
