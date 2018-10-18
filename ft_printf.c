/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:43:13 by ebouvier          #+#    #+#             */
/*   Updated: 2018/10/18 23:31:26 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline uint_fast64_t		parse_width(const char **fmt, va_list ap)
{
	uint_fast64_t	width;

	width = 0;
	if (ft_isdigit(**fmt))
		width = ft_atoi(*fmt);
	else if (**fmt == ASTERISK)
	{
		width = va_arg(ap, int);
	}
	(*fmt)++;
	return (width);
}

static inline void			parse_flags(const char **fmt, t_flags *flags, va_list ap)
{
	while(**fmt)
	{
		if (**fmt == HASH)
			flags->hash = 1;
		else if (**fmt == ZERO)
			flags->zero = 1;
		else if (**fmt == MINUS)
			flags->minus = 1;
		else if (**fmt == PLUS)
			flags->plus = 1;
		else if (**fmt == SPACE)
			flags->space = 1;
		else if (**fmt != HASH && **fmt != ZERO && **fmt != MINUS 
					&& **fmt != PLUS && **fmt != SPACE)
			parse_width(fmt, ap);
		(*fmt)++;
	}
}

static inline void			parse_specifier(const char **fmt, t_flags *flags, va_list ap)
{
	while(**fmt)
	{
		if (**fmt != SPECIFIER)
		{
			ft_putchar(**fmt);
			(*fmt)++;
		}
		else
		{
			(*fmt)++;
			parse_flags(fmt, flags, ap);
		}
	}
}

int							ft_printf(const char *fmt, ...)
{
	va_list ap;
	int     ret;
	t_flags flags;
	
	ret = 0;
	va_start(ap, fmt);
	parse_specifier(&fmt, &flags, ap);
	print_flags(&flags);
	va_end(ap);
	return (ret);
}