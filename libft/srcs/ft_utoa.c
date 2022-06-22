/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:43:19 by severi            #+#    #+#             */
/*   Updated: 2022/02/11 15:46:46 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_unsigned_digits(unsigned long c)
{
	size_t	digits;

	digits = 0;
	while (c > 0)
	{
		digits++;
		c /= 10;
	}
	return (digits);
}

char	*ft_utoa(unsigned int c)
{
	char			*s;
	size_t			digits;
	unsigned long	value;

	value = c;
	digits = count_unsigned_digits(value);
	s = ft_strnew(digits);
	if (s == NULL)
		return (NULL);
	if (c == 0)
		s[0] = '0';
	while (value > 0)
	{
		s[--digits] = (char)((value % 10) + '0');
		value /= 10;
	}
	return (s);
}
