/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_printf.h                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kalnajja <kalnajja@student.42amman.com>   #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/12 17:19:30 by kalnajja         #+#    #+#              */
/*   Updated: 2026/10/16 18:09:15 by kalnajja        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>

// # include <stdio.h>
// # include <limits.h>

int	ft_putchar_fd(char c, int fd);
int	ft_printf(const char *format, ...);
int	ft_putstr_fd(char *s, int fd);
int	ft_putstr_n(char *s, int fd);
int	ft_putnbr_fd(int n, int fd);
int	ft_putnbr_unsigned_fd(unsigned int n, int fd);
int	ft_putnbr_hex_fd(unsigned int n, int fd);
int	ft_putnbr_hex_upper_fd(unsigned int n, int fd);
int	ft_putptr_fd(void *ptr, int fd);
int	ft_handle_format(char specifier, va_list *args);

#endif
