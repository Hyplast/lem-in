/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:43:57 by severi            #+#    #+#             */
/*   Updated: 2022/06/06 10:55:06 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
*	ft_bin_to_int converts the exponent binary string into a decimal string
*	by multiplying corresponding powers of two by '1' bits
*/
char	*ft_bin_to_int(char *vlq)
{
	int		i;
	char	*result;
	char	*temp;
	char	*pow;

	i = 0;
	result = ft_strnew(ft_strlen(vlq) + 1);
	if (!result)
		return (NULL);
	ft_strrev(vlq);
	while (vlq[i] != 0)
	{
		if (vlq[i] == '1')
		{
			pow = vlq_power_of_two(i);
			temp = ft_strdup(result);
			ft_strdel(&result);
			result = vlq_sum(temp, pow);
			ft_strdel(&pow);
			ft_strdel(&temp);
		}
		i++;
	}
	return (result);
}

static char	*compute_sum(char *vlq, char *result, int i, int j)
{
	char	*temp;
	char	*pow;
	char	*temp_pow;

	while (vlq[++i] != '\0')
	{
		if (vlq[i] == '1')
		{
			pow = vlq_power_of_five(i);
			temp_pow = ft_strdup(pow);
			if (!pow || !temp_pow)
				return (NULL);
			ft_strdel(&pow);
			pow = vlq_raise_pow_ten(temp_pow, j);
			temp = ft_strdup(result);
			ft_strdel(&temp_pow);
			ft_strdel(&result);
			result = vlq_sum(temp, pow);
			ft_strdel(&pow);
			ft_strdel(&temp);
		}
		j--;
	}
	return (result);
}

/*
*	ft_bin_to_dec computes the following sum : 
*	(sum 5^(fractional digits - i)
*	which is equal to the decimal part in base 10
*/
char	*ft_bin_to_dec(char *vlq)
{
	int		i;
	int		j;
	char	*result;

	i = -1;
	j = (int)ft_strlen(vlq) - 1;
	result = ft_strnew(ft_strlen(vlq) + 1);
	if (!result)
		return (NULL);
	vlq_initialize(result, '0', (int)ft_strlen(vlq));
	return (compute_sum(vlq, result, i, j));
}
