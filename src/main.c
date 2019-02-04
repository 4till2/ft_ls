/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:56:51 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/14 16:00:39 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		main(int argc, char **argv)
{
	int				k;
	int				i;
	unsigned int	flags;

	i = 1;
	flags = 0;
	while (argc > 0 && argv[i] && argv[i][0] == '-')
	{
		if (argv[i][1] == '-' && !argv[i][2])
		{
			i++;
			break ;
		}
		k = 1;
		while (argv[i][k])
		{
			if ((flags = add_flag(flags, argv[i][k++])) == 0)
				return (-1);
		}
		i++;
	}
	create_lists(&argv[i], flags);
	return (0);
}
