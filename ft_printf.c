/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:43:13 by ebouvier          #+#    #+#             */
/*   Updated: 2018/10/20 18:39:50 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int g_width		= 0x0U;
unsigned int g_precision	= 0x0U;

static inline void	parse_precision(const char *fmt, va_list ap, int *flags)
{
	int p;

	p = 0x0U;
	if (*fmt == '.')
	{
      *flags |= FLAGS_PRECISION;
	  fmt++;
	  if (ft_isdigit(*fmt))
	  {
		  g_precision = (unsigned int) ft_atoi(fmt);
	  }
	  else if (*fmt == '*')
	  {
		  p = va_arg(ap, int);
		  g_precision = p > 0 ? (unsigned int) p : 0x0U;
		  fmt++;
	  }
	}
}

static inline void	parse_width(const char *fmt, va_list ap, int *flags)
{
	int w;

	w = 0x0U;
	if (ft_isdigit(*fmt))
		g_width = (unsigned int) ft_atoi(fmt);
	else if (*fmt == '*')
	{
		w = va_arg(ap, int);
		if (w < 0)
		{
			*flags |= LEFT;
			g_width = (unsigned int)-w; 
		}
		else
			g_width = (unsigned int)w; 
	}
	fmt++;
}

static inline void	parse_flags(const char *fmt, int *flags, va_list ap)
{
	while(*fmt)
	{
		if (*fmt == '#')
			*flags |= HASH;
		else if (*fmt == '0')
			*flags |= ZERO;
		else if (*fmt == '-')
			*flags |= LEFT;
		else if (*fmt == '+')
			*flags |= PLUS;
		else if (*fmt == ' ')
			*flags |= SPACE;
		else
			break;
		fmt++;
	}
	parse_width(fmt, ap, flags);
	parse_precision(fmt, ap, flags);
}

static inline void	parse_specifier(const char *fmt, int *flags, va_list ap, int *ret)
{
	while(*fmt)
	{
		if (*fmt != '%')
		{
			ft_putchar(*fmt);
			(*ret)++;
		}
		else
		{
			fmt++;
			parse_flags(fmt, flags, ap);
		}
		fmt++;
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
	parse_specifier(fmt, &flags, ap, &ret);
	print_flags(&flags);
	va_end(ap);
	return (ret);
}