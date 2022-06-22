/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:37:50 by severi            #+#    #+#             */
/*   Updated: 2022/04/08 00:18:28 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(char c)
{
	ft_putchar(c);
	return (1);
}

int	print_b(t_flags *flag_s, va_list ap, int chars_printed)
{
	char			*s;
	unsigned int	i;

	i = (unsigned int) va_arg(ap, unsigned int);
	s = ft_basetoa(i, 2, ' ');
	chars_printed += print_before(flag_s, chars_printed, s, 'b');
	ft_strdel(&s);
	return (chars_printed);
}

void	ft_add_zeros(char **str, int zeros)
{
	char	*str_0;
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(*str);
	str_0 = ft_strnew(zeros + len);
	ft_strncpy(str_0, *str, len);
	while (i < zeros)
	{
		str_0[len + i] = '0';
		i++;
	}
	ft_strdel(str);
	*str = ft_strdup(str_0);
	ft_strdel(&str_0);
}

char	*shorten_chars(char *str, int start, int end)
{
	char	*temp;

	temp = ft_strsub(str, start, ft_strlen(str) - end);
	ft_strclr(str);
	str = ft_memcpy(str, temp, ft_strlen(temp));
	ft_strdel(&temp);
	return (str);
}
