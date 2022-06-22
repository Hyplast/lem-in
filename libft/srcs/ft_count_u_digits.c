/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_u_digits.c                                :+:      :+:    :+:   */
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
