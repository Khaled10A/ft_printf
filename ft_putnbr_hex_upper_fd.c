/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_putnbr_hex_upper_fd.c                          :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kalnajja <kalnajja@student.42amman.com>   #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/14 10:44:41 by kalnajja         #+#    #+#              */
/*   Updated: 2026/10/16 18:08:40 by kalnajja        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex_upper_fd(unsigned int n, int fd)
{
	char			*hex_digits;
	unsigned int	quotient;
	unsigned int	remainder;
	int				count;

	hex_digits = "0123456789ABCDEF";
	count = 0;
	quotient = n / 16;
	remainder = n % 16;
	if (n >= 16)
		count += ft_putnbr_hex_upper_fd(quotient, fd);
	count += ft_putchar_fd(hex_digits[remainder], fd);
	return (count);
}
/*
int main()
{
ft_putnbr_hex_upper_fd(42, 1);     // 2A
ft_putchar_fd('\n', 1);
ft_putnbr_hex_upper_fd(255, 1);    // FF
ft_putchar_fd('\n', 1);
ft_putnbr_hex_upper_fd(48879, 1);  // BEEF
return (0);
}
*/
