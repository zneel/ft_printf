/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:43:13 by ebouvier          #+#    #+#             */
/*   Updated: 2018/11/02 12:06:04 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int g_width		= 0U;
unsigned int g_precision	= 0U;


/*
** output_char
** output a char and increment return value
*/

static inline void	output_char(char c, int *ret)
{
	write(1, &c, 1);
	++*ret;
}

/*
** convert_string
** handle the string output
*/

static inline void	convert_s(const char **fmt, int *flags, va_list ap, int *ret)
{
	char *p_str;
	unsigned int len;

	p_str = va_arg(ap, char*);
	if (p_str == NULL)
		p_str = "(null)";
	len = ft_strlen(p_str);	
	if (*flags & F_P)
		len = (len < g_precision ? len : g_precision);
	if (!(*flags & LEFT))
		while (len++ < g_width)
			output_char(' ', ret);
	while (*p_str && (!(*flags & F_P) || g_precision--))
		output_char(*(p_str++), ret);
	if (*flags & LEFT)
		while (len++ < g_width)
			output_char(' ', ret);
	++*fmt;
}

/*
**	convert_char
**	We're always starting at 1 because we're printing a char...
**	First we check the LEFT padding flag for pre-padding
**	(!(*flags & LEFT)) means that we're checking if the bitmask isn't set in flags
**	.... priting the char ....
**	Then we check the LEFT padding flag to print post-padding
**	(*flags & LEFT) means that we're checking if the bitmask is set in flags
*/

static inline void	convert_c(const char **fmt, int *flags, va_list ap, int *ret)
{
	unsigned int l;

	l = 1U;
	if (!(*flags & LEFT))
		while (l++ < g_width)
			output_char(' ', ret);
	output_char((char)va_arg(ap, int), ret);
	if (*flags & LEFT)
		while (l++ < g_width)
			output_char(' ', ret);
	++*fmt;	
}

static inline void convert_d(const char **fmt, int *flags, va_list ap, int *ret)
{

}

/*
**	convert_percent
**	We're just printing a %
*/

static inline void	convert_percent(const char **fmt, int *flags, va_list ap, int *ret)
{
	(void)flags;
	(void)ap;
	output_char('%', ret);
	++*fmt;
}

/*
**	convert_default
**	Printing dereferenced fmt
*/

static inline void	convert_default(const char **fmt, int *flags, va_list ap, int *ret)
{
	(void)flags;
	(void)ap;
	output_char(**fmt, ret);
	++*fmt;
}

/*
**	parse_convert
**	Checking wich function we need to call for the current **fmt
*/

static inline void	parse_convert(const char **fmt, int *flags, va_list ap, int *ret)
{
	if (**fmt == 's')
		convert_s(fmt, flags, ap, ret);
	else if (**fmt == 'c')
		convert_c(fmt, flags, ap, ret);
	else if (**fmt == '%')
		convert_percent(fmt, flags, ap, ret);
	else 
		convert_default(fmt, flags, ap, ret);
}

/*
**	parse_precision
**	Checking the precision
**	If we encounter a '.' in **fmt we're turning on the flag.
**	|= is setting the bitmask
**  the flag for precision is 1024U
**	*flags == 0100 0000 0000
*/

static inline void	parse_precision(const char **fmt, int *flags, va_list ap)
{
	int p;

	p = 0U;
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
			g_precision = p > 0 ? (unsigned int) p : 0U;
			++*fmt;
		}
	}
}

/*
**	parse_width
**	Parsing the width
*/

static inline void	parse_width(const char **fmt, int *flags, va_list ap)
{
	int w;

	w = 0U;
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

/*
**	parse_flags
**	Parsing the flags and activating some bit masks
**	|= is setting the bitmask
**	eg:
**		- we're activating the # flag (1U)
**			- *flags == 0000 0000 0001 // 1
**		- then we're activating the - flag (4U)
**			- *flags == 0000 0000 0101 // 5
*/

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

/*
**	parse_specifier
**	Checking the specifier
*/

static inline void	parse_specifier(const char **fmt, int *flags, va_list ap, int *ret)
{
	while(**fmt)
	{
		if (**fmt != '%')
		{
			output_char(**fmt, ret);
			++*fmt;
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
	flags = 0U;
	va_start(ap, fmt);
	parse_specifier(&fmt, &flags, ap, &ret);
	ft_putchar(0);
	va_end(ap);
	return (ret);
}