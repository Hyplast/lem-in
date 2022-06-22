/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 01:47:10 by severi            #+#    #+#             */
/*   Updated: 2022/05/18 18:45:13 by ssavukos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_u(t_flags *flag_s, va_list ap, int chars_printed)
{
	char			*s;
	uintmax_t		u;

	u = unsigned_conv(flag_s, ap);
	if (u == 0 && flag_s->prec != 0)
		return (chars_printed += print_c('0'));
	else if (u == 0 && flag_s->prec == 0 && flag_s->sharp == 1)
		return (chars_printed);
	else if (u == 0 && flag_s->prec == 0)
		return (chars_printed += print_before(flag_s, chars_printed, "", 32));
	if (flag_s->spec == 1 || flag_s->spec == 2)
		s = ft_lutoa(u);
	else
		s = ft_utoa(u);
	chars_printed += print_before(flag_s, chars_printed, s, 'u');
	ft_strdel(&s);
	return (chars_printed);
}

int	print_o(t_flags *flag_s, va_list ap, int chars_printed)
{
	char			*s;
	uintmax_t		o;

	o = unsigned_conv(flag_s, ap);
	if (o == 0)
	{
		if (flag_s->width != 0)
			return (print_before(flag_s, chars_printed, "", 'o'));
		else if (o == 0 && flag_s->prec == 0)
			return (chars_printed += print_before(flag_s,
					chars_printed, "", 'o'));
		return (chars_printed += print_c('0'));
	}
	s = ft_basetoa(o, 8, ' ');
	chars_printed += print_before(flag_s, chars_printed, s, 'o');
	ft_strdel(&s);
	return (chars_printed);
}

int	print_x(t_flags *flag_s, va_list ap, int chars_printed)
{
	char		*s;
	uintmax_t	x;

	x = unsigned_conv(flag_s, ap);
	if ((x == 0 && flag_s->prec != 0 && flag_s->len == 0)
		|| (x == 0 && flag_s->sharp == 1 && flag_s->len == 1))
		return (chars_printed += print_c('0'));
	else if (x == 0 && flag_s->prec == 0 && flag_s->sharp == 1)
		return (chars_printed);
	else if (x == 0 && flag_s->prec == 0)
		return (chars_printed += print_before(flag_s, chars_printed, "", 32));
	s = ft_basetoa(x, 16, ' ');
	chars_printed += print_before(flag_s, chars_printed, s, 'x');
	ft_strdel(&s);
	return (chars_printed);
}

int	print_big_x(t_flags *flag_s, va_list ap, int chars_printed)
{
	char		*s;
	int			j;
	uintmax_t	x;

	j = 0;
	x = unsigned_conv(flag_s, ap);
	if (x == 0 && flag_s->prec != 0 && flag_s->len == 0)
		return (chars_printed += print_c('0'));
	else if (x == 0 && flag_s->prec == 0 && flag_s->sharp == 1)
		return (chars_printed);
	else if (x == 0 && flag_s->prec == 0)
		return (chars_printed += print_before(flag_s, chars_printed, "", 32));
	s = ft_basetoa(x, 16, ' ');
	while (s[j] != '\0')
	{
		s[j] = (char)ft_toupper(s[j]);
		j++;
	}
	chars_printed += print_before(flag_s, chars_printed, s, 'X');
	ft_strdel(&s);
	return (chars_printed);
}
