/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_printf.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kalnajja <kalnajja@student.42amman.com>   #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/12 12:01:01 by kalnajja         #+#    #+#              */
/*   Updated: 2026/10/16 18:08:31 by kalnajja        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	handle_error(va_list *args)
{
	va_end(*args);
	return (-1);
}

static int	ft_handle_conversion(const char *format, int *i, va_list *args)
{
	int	ret;

	ret = ft_handle_format(format[*i + 1], args);
	if (ret == -1)
		return (-1);
	(*i) += 2;
	return (ret);
}

static int	ft_print_regular_char(const char *format, int *i)
{
	int	ret;

	ret = write(1, &format[*i], 1);
	if (ret == -1)
		return (-1);
	(*i)++;
	return (ret);
}

static int	ft_process_format(const char *format, int *i, va_list *args)
{
	int	ret;

	if (format[*i] == '%' && format[*i + 1] != '\0')
		ret = ft_handle_conversion(format, i, args);
	else
		ret = ft_print_regular_char(format, i);
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;
	int		ret;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		ret = ft_process_format(format, &i, &args);
		if (ret == -1)
			return (handle_error(&args));
		count += ret;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	int	a = ft_printf("100%y\n");
// 	//int	b = printf("100%y\n");

// 	printf("a=%d", a);
// }
