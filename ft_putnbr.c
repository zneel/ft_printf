/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 22:47:46 by ebouvier          #+#    #+#             */
/*   Updated: 2018/11/01 13:12:32 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(long long n)
{
	if (n == __LONG_LONG_MAX__)
	{
		ft_putstr("9223372036854775807");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}
