/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_putnbr_hex_fd.c                                :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kalnajja <kalnajja@student.42amman.com>   #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/13 21:33:42 by kalnajja         #+#    #+#              */
/*   Updated: 2026/10/16 18:08:38 by kalnajja        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex_fd(unsigned int n, int fd)
{
	char			*hex_digits;
	unsigned int	quotient;
	unsigned int	remainder;
	int				count;

	hex_digits = "0123456789abcdef";
	count = 0;
	quotient = n / 16;
	remainder = n % 16;
	if (n >= 16)
		count += ft_putnbr_hex_fd(quotient, fd);
	count += ft_putchar_fd(hex_digits[remainder], fd);
	return (count);
}
/*
int main()
{
ft_putnbr_hex_fd(0, 1);           // 0
ft_putchar_fd('\n', 1);
ft_putnbr_hex_fd(42, 1);          // 2a
ft_putchar_fd('\n', 1);
ft_putnbr_hex_fd(255, 1);         // ff
ft_putchar_fd('\n', 1);
ft_putnbr_hex_fd(4294967295U, 1); // ffffffff
return (0);
}
*/
