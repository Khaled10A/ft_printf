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
/*
#include <stdio.h>
#include <limits.h>

int main()
{
int n = 42;
char *s = NULL;

ft_printf("%c\n", 'A');
printf("%c\n", 'A');

ft_printf("%s\n", "hello");
printf("%s\n", "hello");

ft_printf("[%s]\n", s);
printf("[%s]\n", s);

ft_printf("%d\n", -42);
printf("%d\n", -42);

ft_printf("%d\n", INT_MIN);
printf("%d\n", INT_MIN);

ft_printf("%i\n", INT_MAX);
printf("%i\n", INT_MAX);

ft_printf("%u\n", UINT_MAX);
printf("%u\n", UINT_MAX);

ft_printf("%x\n", 255);
printf("%x\n", 255);

ft_printf("%X\n", 48879);
printf("%X\n", 48879);

ft_printf("%x\n", -1);
printf("%x\n", -1);

ft_printf("%p\n", (void *)0);
printf("%p\n", (void *)0);

ft_printf("%p\n", &n);
printf("%p\n", &n);

ft_printf("100%%\n");
printf("100%%\n");

ft_printf("%c %s %d %x\n", 'z', "ok", -7, 255);
printf("%c %s %d %x\n", 'z', "ok", -7, 255);
return (0);
}
*/
