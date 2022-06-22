/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 09:54:52 by severi            #+#    #+#             */
/*   Updated: 2022/05/22 14:22:10 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_modifiers(const char *flags, const char *modifiers, int len)
{
	int	len_max;
	int	j;
	int	i;

	len_max = ft_strlen(flags);
	if (len_max < len)
		len = len_max;
	i = 0;
	j = 0;
	while (flags[i] != '\0' && modifiers[j] != '\0')
	{
		if (flags[i] == modifiers[j])
		{
			i++;
			j = -1;
		}
		j++;
	}
	return (i);
}

static int	valid_order(const char *flags, int len)
{
	int	i;

	i = 0;
	i += check_modifiers(flags, VALID_FLAGS, len);
	i += check_modifiers(flags + i, VALID_WIDTH, len);
	i += check_modifiers(flags + i, ".", len);
	i += check_modifiers(flags + i, VALID_PREC, len);
	i += check_modifiers(flags + i, VALID_SPECI, len);
	if (i == len)
		return (2);
	i += check_modifiers(flags + i, VALID_FORMAT, len);
	if (i == len)
		return (1);
	return (0);
}

static	char	*parse_specifier(const char *flags)
{
	size_t	len;
	int		i;
	int		elem;
	char	*temp;

	i = 0;
	elem = ft_strlen(VALID_FORMAT);
	len = 0;
	if (*flags == '%')
		return (ft_strdup("%"));
	while (flags[len] != '\0' && flags[len] != '%')
	{
		while (flags[len] != VALID_FORMAT[i] && i < elem)
			i++;
		if (flags[len] == VALID_FORMAT[i])
			return (ft_strsub(flags, 0, len + 1));
		i = 0;
		len++;
	}
	temp = ft_strnew(len + 1);
	while (i < (int)len + 1)
		temp[i++] = '\1';
	if (valid_order(flags, len) == 2 && flags[len] == '%')
		temp[0] = '%';
	return (temp);
}

static int	read_while(const char *format, va_list ap, int i, int chars_printed)
{
	char	*flags;

	while (i != -1)
	{
		chars_printed += ft_putnchar(format, (size_t)i);
		format = ft_strchr(format, '%') + 1;
		if (ft_strcmp(format, "") == 0 && chars_printed == 0)
			return (0);
		flags = parse_specifier(format);
		if (flags[0] != '%' && flags[0] != '\1')
			chars_printed += read_flags(flags, ap);
		else if (flags[0] == '%')
			chars_printed += ft_putnchar("%", 1);
		else
		{
			chars_printed += ft_putnchar("%", 1);
			chars_printed += ft_putnchar(format, ft_strlen(flags));
		}
		format += ft_strlen(flags);
		ft_strdel(&flags);
		i = ft_lookforchar(format, '%');
	}
	chars_printed += ft_putnchar(format, ft_strlen(format));
	return (chars_printed);
}

/*
*	Print function, use % with specifiers.
*
*	@param string in ("string %'x'", %bcdfiopsuxX) -format
*	@return Number characters written in stdout
*/
int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		chars_printed;

	va_start(ap, format);
	chars_printed = 0;
	i = ft_lookforchar(format, '%');
	chars_printed = read_while(format, ap, i, chars_printed);
	va_end(ap);
	return (chars_printed);
}
