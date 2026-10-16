/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_putptr_fd.c                                    :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kalnajja <kalnajja@student.42amman.com>   #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/14 13:00:36 by kalnajja         #+#    #+#              */
/*   Updated: 2026/10/16 18:08:45 by kalnajja        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_putptr_hex(uintptr_t n, int fd)
{
	char	*hex_digits;
	int		count;

	hex_digits = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_putptr_hex(n / 16, fd);
	count += ft_putchar_fd(hex_digits[n % 16], fd);
	return (count);
}

int	ft_putptr_fd(void *ptr, int fd)
{
	uintptr_t	address;
	int			count;

	if (ptr == NULL)
		return (ft_putstr_n("(nil)", fd));
	count = 0;
	address = (uintptr_t) ptr;
	count += ft_putstr_n("0x", fd);
	count += ft_putptr_hex(address, fd);
	return (count);
}
/*
int main()
{
//ft_putptr_fd(NULL, 1);
int	n;

n = 42;
printf("Original: %p\n", (void *)&n);
ft_putptr_fd(&n, 1);
printf("\n");
return (0);
}
*/
