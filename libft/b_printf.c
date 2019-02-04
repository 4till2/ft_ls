/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_printf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 15:27:07 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/14 10:08:47 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_printflag(char *traverse, va_list arg)
{
	if (*traverse == '%')
		ft_putchar('%');
	else if (*traverse == 's')
		ft_putstr(va_arg(arg, char *));
	else if (*traverse == 'c')
		ft_putchar(va_arg(arg, int));
	else if (*traverse == 'i' || *traverse == 'd')
		ft_putnbr_base(va_arg(arg, int), 10);
	else if (*traverse == 'o')
		ft_putnbr_base(va_arg(arg, unsigned int), 8);
	else if (*traverse == 'x')
		ft_putnbr_base(va_arg(arg, unsigned int), 16);
	else if (*traverse == 'p')
	{
		ft_putstr("0x");
		ft_putnbr_base((long long)va_arg(arg, void*), 16);
	}
	else if (*traverse == 'u')
		ft_putnbr_base(va_arg(arg, unsigned int), 10);
}

int				b_printf(const char *restrict format, ...)
{
	char	*traverse;
	va_list	arg;

	va_start(arg, format);
	traverse = (char*)format;
	while (*traverse != '\0')
	{
		while (*traverse != '%' && *traverse != '\0')
		{
			ft_putchar(*traverse);
			traverse++;
		}
		if (*traverse == '\0')
			break ;
		traverse++;
		ft_printflag(traverse, arg);
		traverse++;
	}
	va_end(arg);
	return (0);
}
