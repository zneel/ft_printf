/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 20:15:45 by ebouvier          #+#    #+#             */
/*   Updated: 2018/10/18 22:39:20 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    print_flags(t_flags *flags)
{
    ft_putstr_fd("Printing value of hash ", 1);
    ft_putnbr(flags->hash);
    ft_putstr_fd("\n", 1);
    ft_putstr_fd("Printing value of zero ", 1);
    ft_putnbr(flags->zero);
    ft_putstr_fd("\n", 1);
    ft_putstr_fd("Printing value of minus ", 1);
    ft_putnbr(flags->minus);
    ft_putstr_fd("\n", 1);
    ft_putstr_fd("Printing value of plus ", 1);
    ft_putnbr(flags->plus);
    ft_putstr_fd("\n", 1);
    ft_putstr_fd("Printing value of space ", 1);
    ft_putnbr(flags->space);
    ft_putstr_fd("\n", 1);
}