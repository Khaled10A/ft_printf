/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_putstr_fd.c                                    :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kalnajja <kalnajja@student.42amman.com>   #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/12 17:19:26 by kalnajja         #+#    #+#              */
/*   Updated: 2026/10/16 18:08:46 by kalnajja        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL || fd < 0)
		return (0);
	while (s[i] != '\0')
	{
		if (ft_putchar_fd(s[i], fd) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_putstr_n(char *s, int fd)
{
	if (s == NULL)
		return (ft_putstr_fd("(null)", fd));
	return (ft_putstr_fd(s, fd));
}
