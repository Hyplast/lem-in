/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 09:54:52 by severi            #+#    #+#             */
/*   Updated: 2022/05/22 14:22:10 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	match_function(t_flags *flags, va_list ap, int c, int printed_c)
{
	if (c == 'b')
		printed_c += print_b(flags, ap, printed_c);
	else if (c == 'c')
		printed_c += print_char(flags, (char) va_arg(ap, int), printed_c);
	else if (c == 'd')
		printed_c += print_d(flags, ap, printed_c);
	else if (c == 'f')
		printed_c += print_f(flags, ap, printed_c);
	else if (c == 'i')
		printed_c += print_i(flags, ap, printed_c);
	else if (c == 'o')
		printed_c += print_o(flags, ap, printed_c);
	else if (c == 'p')
		printed_c += print_p(flags, ap, printed_c);
	else if (c == 's')
		printed_c += print_s(flags, (char *) va_arg(ap, char *), printed_c);
	else if (c == 'u')
		printed_c += print_u(flags, ap, printed_c);
	else if (c == 'x')
		printed_c += print_x(flags, ap, printed_c);
	else if (c == 'X')
		printed_c += print_big_x(flags, ap, printed_c);
	return (printed_c);
}

int	read_flags(char *flags, va_list ap)
{
	int		chars_printed;
	size_t	len;
	t_flags	*flag_s;

	flag_s = return_flags(flags);
	len = ft_strlen(flags);
	chars_printed = 0;
	chars_printed = match_function(flag_s, ap, flags[len - 1], 0);
	free_flags(flag_s);
	return (chars_printed);
}
