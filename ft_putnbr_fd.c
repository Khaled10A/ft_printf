/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_putnbr_fd.c                                    :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kalnajja <kalnajja@student.42amman.com>   #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/13 15:08:45 by kalnajja         #+#    #+#              */
/*   Updated: 2026/10/16 18:08:36 by kalnajja        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		count;
	long	nb;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		count += ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	if (nb >= 10)
		count += ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd((nb % 10) + '0', fd);
	count++;
	return (count);
}
/*
int main(void)
{
ft_putnbr_fd(-42, 1);
ft_putchar_fd('\n', 1);
return (0);
}
*/
