/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                 :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 01:00:08 by severi            #+#    #+#             */
/*   Updated: 2022/05/22 14:37:15 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_section(t_flags *flag, int c_p, char *s, char c)
{
	if (flag->plus == 1)
		c_p = is_plus(flag, c_p, &s, c);
	if (flag->sharp == 1)
		c_p = is_sharp(c_p, c);
	return (c_p);
}

int	print_minus(t_flags *flag, int c_p, char *s, char c)
{
	if (flag->space == 1 && s[0] != '-')
		c_p += print_c(' ');
	c_p = print_sign(flag, c_p, &s);
	c_p = print_section(flag, c_p, s, c);
	c_p += ft_putcx('0', flag->prec - ft_strlen(s) - flag->plus);
	c_p += ft_putnchar(s, ft_strlen(s));
	if (flag->zero == 1)
		c_p += ft_putcx('0', flag->width - c_p);
	else
		c_p += ft_putcx(' ', flag->width - c_p);
	return (c_p);
}

int	print_u_int(t_flags *flag, int c_p, char *s, char c)
{
	if (flag->minus == 0 && flag->sharp == 0 && flag->zero == 0)
		c_p += print_normal(flag, c_p, s, c);
	if (flag->minus == 0 && flag->sharp == 0 && flag->zero == 1)
		c_p += print_w_zeros(flag, c_p, s, c);
	if (flag->minus == 0 && flag->sharp == 1 && flag->zero == 1)
		c_p += print_sharp_w_zeros(flag, c_p, s, c);
	if (flag->minus == 0 && flag->sharp == 1 && flag->zero == 0)
		c_p += print_sharp_w_spaces(flag, c_p, s, c);
	if (flag->minus == 1 && flag->sharp == 0)
		c_p += print_minus(flag, c_p, s, c);
	else if (flag->minus == 1)
		c_p += print_minus(flag, c_p, s, c);
	return (c_p);
}
