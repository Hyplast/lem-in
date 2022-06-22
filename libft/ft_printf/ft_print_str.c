/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 01:00:08 by severi            #+#    #+#             */
/*   Updated: 2022/05/22 14:37:15 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	with_non_minus(t_flags *flag, int c_p)
{
	if (flag->zero == 1)
		c_p += ft_putcx('0', flag->width - c_p);
	else
		c_p += ft_putcx(' ', flag->width - c_p);
	return (c_p);
}

int	print_str_w_flags(t_flags *flag, int c_p, char *s)
{
	c_p += ft_strlen(s);
	if (flag->minus == 0)
		c_p = with_non_minus(flag, c_p);
	ft_putnchar(s, ft_strlen(s));
	if (flag->minus == 1)
	{
		if (flag->zero == 1)
		{
			c_p += ft_putcx('0', flag->width - c_p);
			if (flag->width != 0)
				c_p += ft_putcx('0', flag->width - flag->prec - c_p);
		}
		else
		{
			c_p += ft_putcx(' ', flag->width - c_p);
			if (flag->width != 0 && flag->prec != -1)
				c_p += ft_putcx(' ', flag->width - flag->prec - c_p);
		}
	}
	return (c_p);
}
