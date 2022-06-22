/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_signed.c                                   :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 01:00:08 by severi            #+#    #+#             */
/*   Updated: 2022/05/22 14:37:15 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_normal(t_flags *flag, int c_p, char *s, char c)
{
	if (flag->prec > (int)ft_strlen(s))
		c_p += flag->prec;
	else
		c_p += (int)ft_strlen(s);
	if (flag->prec >= (int)ft_strlen(s) - flag->plus && s[0] == '-')
		c_p += 1;
	if (flag->space == 1 && s[0] != '-' && (c == 'i' || c == 'd'))
		c_p += print_c(' ');
	c_p += ft_putcx(' ', flag->width - c_p - flag->plus);
	print_sign(flag, c_p, &s);
	c_p = print_section(flag, c_p, s, c);
	if (flag->prec > (int)ft_strlen(s) - flag->plus)
		ft_putcx('0', flag->prec - ft_strlen(s) - flag->plus);
	else
		c_p += ft_putcx('0', flag->prec - (int)ft_strlen(s) - flag->plus);
	if (flag->minus == 1)
		ft_putnchar(s, ft_strlen(s));
	if (flag->minus == 0)
		ft_putnchar(s, ft_strlen(s));
	return (c_p);
}

int	print_sharp_w_zeros(t_flags *flag, int c_p, char *s, char c)
{
	c_p += print_section(flag, c_p, s, c);
	c_p += ft_putcx('0', flag->width - ft_strlen(s) - c_p);
	if (flag->minus == 1)
		c_p += ft_putnchar(s, ft_strlen(s));
	if (flag->minus == 0)
		c_p += ft_putnchar(s, ft_strlen(s));
	return (c_p);
}

int	print_sharp_w_spaces(t_flags *flag, int c_p, char *s, char c)
{
	c_p += 1;
	if (c != 'o')
		c_p += 1;
	c_p += ft_putcx(' ', flag->width - ft_strlen(s) - c_p);
	print_section(flag, c_p, s, c);
	c_p += ft_putcx('0', flag->prec - ft_strlen(s));
	if (flag->minus == 1)
		c_p += ft_putnchar(s, ft_strlen(s));
	if (flag->minus == 0)
		c_p += ft_putnchar(s, ft_strlen(s));
	return (c_p);
}

int	print_w_zeros(t_flags *flag, int c_p, char *s, char c)
{
	c_p += print_sign(flag, c_p, &s);
	if (flag->plus == 1)
		c_p += is_plus(flag, c_p, &s, c);
	if (flag->prec > (int)ft_strlen(s))
		c_p += flag->prec - ft_strlen(s);
	if (flag->space == 1 && s[0] != '-')
		c_p += print_c(' ');
	if (flag->zero == 1)
		c_p += ft_putcx('0', flag->width - ft_strlen(s) - c_p);
	else
		c_p += ft_putcx(' ', flag->width - ft_strlen(s) - c_p);
	ft_putcx('0', flag->prec - ft_strlen(s) - flag->plus);
	c_p = print_section(flag, c_p, s, c);
	c_p += ft_putnchar(s, ft_strlen(s));
	return (c_p);
}

int	print_int(t_flags *flag, int c_p, char *s, char c)
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
