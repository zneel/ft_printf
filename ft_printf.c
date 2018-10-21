/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:43:13 by ebouvier          #+#    #+#             */
/*   Updated: 2018/10/21 23:44:26 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int g_width		= 0x0U;
unsigned int g_precision	= 0x0U;

static inline void	convert_c(const char **fmt, int *flags, va_list ap, int *ret)
{
	unsigned int len;
	len = 0x1U;

	if (!(*flags & LEFT))
	{
		while (len++ < g_width)
		{
			ft_putchar(' ');
			(*ret)++;
		}
	}
	ft_putchar((char)va_arg(ap, int));
	(*ret)++;
	if (*flags & LEFT)
	{
		while (len++ < g_width)
		{
			ft_putchar(' ');
			(*ret)++;
		}
	}
	++*fmt;
}

static inline void	parse_convert(const char **fmt, int *flags, va_list ap, int *ret)
{
	if (**fmt == 'c')
	{
		convert_c(fmt, flags, ap, ret);
		++*fmt;
	}
}

static inline void	parse_precision(const char **fmt, int *flags, va_list ap)
{
	int p;

	p = 0x0U;
	if (**fmt == '.')
	{
		*flags |= F_P;
		++*fmt;
		if (ft_isdigit(**fmt))
		{
			g_precision = (unsigned int) ft_atoi(*fmt);
			while (ft_isdigit(**fmt))
				++*fmt;
		}
		else if (**fmt == '*')
		{
			p = va_arg(ap, int);
			g_precision = p > 0 ? (unsigned int) p : 0x0U;
			++*fmt;
		}
	}
}

static inline void	parse_width(const char **fmt, int *flags, va_list ap)
{
	int w;

	w = 0x0U;
	if (ft_isdigit(**fmt))
	{
		g_width = (unsigned int) ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			++*fmt;
	}
	else if (**fmt == '*')
	{
		w = va_arg(ap, int);
		if (w < 0)
		{
			*flags |= LEFT;
			g_width = (unsigned int)-w;
		}
		else
			g_width = (unsigned int)w;
		++*fmt;
	}
}

static inline void	parse_flags(const char **fmt, int *flags, va_list ap, int *ret)
{
	while(**fmt)
	{
		if (**fmt == '#')
			*flags |= HASH;
		else if (**fmt == '0')
			*flags |= ZERO;
		else if (**fmt == '-')
			*flags |= LEFT;
		else if (**fmt == '+')
			*flags |= PLUS;
		else if (**fmt == ' ')
			*flags |= SPACE;
		else
			break;
		++*fmt;
	}
	parse_width(fmt, flags, ap);
	parse_precision(fmt, flags, ap);
	parse_convert(fmt, flags, ap, ret);
}

static inline void	parse_specifier(const char **fmt, int *flags, va_list ap, int *ret)
{
	while(**fmt)
	{
		if (**fmt != '%')
		{
			ft_putchar(**fmt);
			++*fmt;
			(*ret)++;
			continue;
		}
		else
		{
			++*fmt;
			parse_flags(fmt, flags, ap, ret);
		}
	}
}

int					ft_printf(const char *fmt, ...)
{
	va_list ap;
	int     ret;
	int		flags;
	
	ret = 0;
	flags = 0x0U;
	va_start(ap, fmt);
	parse_specifier(&fmt, &flags, ap, &ret);
	va_end(ap);
	return (ret);
}