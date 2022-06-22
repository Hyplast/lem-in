/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:04:28 by severi            #+#    #+#             */
/*   Updated: 2022/03/11 01:10:31 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	signed_conv(t_flags *flag_s, va_list ap)
{
	uintmax_t		i;

	if (flag_s->spec == 0)
		i = (signed int) va_arg(ap, signed int);
	else if (flag_s->spec == 1)
		i = (signed long int) va_arg(ap, signed long int);
	else if (flag_s->spec == 2)
		i = (signed long long int) va_arg(ap, signed long long int);
	else if (flag_s->spec == 4)
		i = (signed short int) va_arg(ap, signed int);
	else if (flag_s->spec == 5)
		i = (signed char) va_arg(ap, unsigned int);
	else
		i = (signed int) va_arg(ap, signed int);
	return (i);
}

uintmax_t	unsigned_conv(t_flags *flag_s, va_list ap)
{
	uintmax_t		u;

	if (flag_s->spec == 0)
		u = (unsigned int) va_arg(ap, unsigned int);
	else if (flag_s->spec == 1)
		u = (unsigned long int) va_arg(ap, unsigned long int);
	else if (flag_s->spec == 2)
		u = (unsigned long long int) va_arg(ap, unsigned long long int);
	else if (flag_s->spec == 4)
		u = (unsigned short int) va_arg(ap, unsigned int);
	else if (flag_s->spec == 5)
		u = (unsigned char) va_arg(ap, unsigned int);
	else
		u = (unsigned int) va_arg(ap, unsigned int);
	return (u);
}
