/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_putnbr_unsigned_fd.c                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kalnajja <kalnajja@student.42amman.com>   #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/13 16:23:13 by kalnajja         #+#    #+#              */
/*   Updated: 2026/10/16 18:08:42 by kalnajja        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	int	count;
	int	ret;

	count = 0;
	if (fd < 0)
		return (-1);
	if (n >= 10)
	{
		ret = ft_putnbr_unsigned_fd(n / 10, fd);
		if (ret == -1)
			return (-1);
		count += ret;
	}
	ret = ft_putchar_fd((n % 10) + '0', fd);
	if (ret == -1)
		return (-1);
	count += ret;
	return (count);
}
