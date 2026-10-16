/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_handle_format.c                                :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kalnajja <kalnajja@student.42amman.com>   #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/14 15:31:07 by kalnajja         #+#    #+#              */
/*   Updated: 2026/10/16 18:08:29 by kalnajja        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_unknown(char specifier)
{
	int	count;
	int	ret;

	count = ft_putchar_fd('%', 1);
	if (count == -1)
		return (-1);
	ret = ft_putchar_fd(specifier, 1);
	if (ret == -1)
		return (-1);
	return (count + ret);
}

int	ft_handle_format(char specifier, va_list *args)
{
	if (specifier == 'c')
		return (ft_putchar_fd(va_arg(*args, int), 1));
	else if (specifier == 's')
		return (ft_putstr_n(va_arg(*args, char *), 1));
	else if (specifier == 'p')
		return (ft_putptr_fd(va_arg(*args, void *), 1));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(*args, int), 1));
	else if (specifier == 'u')
		return (ft_putnbr_unsigned_fd(va_arg(*args, unsigned int), 1));
	else if (specifier == 'x')
		return (ft_putnbr_hex_fd(va_arg(*args, unsigned int), 1));
	else if (specifier == 'X')
		return (ft_putnbr_hex_upper_fd(va_arg(*args, unsigned int), 1));
	else if (specifier == '%')
		return (ft_putchar_fd('%', 1));
	else
		return (ft_print_unknown(specifier));
}
