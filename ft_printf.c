/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:43:13 by ebouvier          #+#    #+#             */
/*   Updated: 2018/10/19 00:17:56 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void	parse_width(const char *fmt, t_flags *flags, va_list ap)
{
	if (ft_isdigit(*fmt))
		flags->width = ft_atoi(fmt);
	else if (*fmt == '*')
		flags->width = va_arg(ap, int);
	fmt++;
}

static inline void	parse_flags(const char *fmt, t_flags *flags, va_list ap)
{
	while(*fmt)
	{
		if (*fmt == '#')
			flags->hash = 1U;
		else if (*fmt == '0')
			flags->zero = 1U;
		else if (*fmt == '-')
			flags->minus = 1U;
		else if (*fmt == '+')
			flags->plus = 1U;
		else if (*fmt == ' ')
			flags->space = 1U;
		else
			break;
		fmt++;
	}
	parse_width(fmt, flags, ap);
}

static inline void	parse_specifier(const char *fmt, t_flags *flags, va_list ap)
{
	while(*fmt)
	{
		if (*fmt != '%')
			ft_putchar(*fmt);
		else
		{
			fmt++;
			parse_flags(fmt, flags, ap);
		}
		fmt++;
	}
}

static inline void	init_flags(t_flags *flags)
{
	flags->hash		= 0U;
	flags->zero		= 0U;
	flags->minus	= 0U;
	flags->plus		= 0U;
	flags->space	= 0U;
	flags->width	= 0U;
}

int					ft_printf(const char *fmt, ...)
{
	va_list ap;
	int     ret;
	t_flags flags;
	
	ret = 0;
	va_start(ap, fmt);
	init_flags(&flags);
	parse_specifier(fmt, &flags, ap);
	print_flags(&flags);
	va_end(ap);
	return (ret);
}