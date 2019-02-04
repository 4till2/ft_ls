/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 08:47:26 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/14 10:08:27 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(long long num, int base)
{
	unsigned long long unum;

	if (num < 0 && base == 10)
	{
		ft_putchar('-');
		ft_putnbr_base(-num, base);
	}
	else
	{
		if (num >= base)
			ft_putnbr_base((num / base), base);
		unum = (unsigned long long)num;
		if ((unum % base) >= 10)
			ft_putchar(((unum % base) - 10 + 'a'));
		else
			ft_putchar(((unum % base) + '0'));
	}
}
