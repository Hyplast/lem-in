/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frexpl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:32:12 by severi            #+#    #+#             */
/*   Updated: 2022/03/11 01:58:33 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
*	fill_nb fills the string "str" with 0's and 1's from "temp"
*/
static void	fill_nb(char *str, unsigned char *temp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 8)
		{
			if (temp[i] & 1)
				str[k] = '1';
			else
				str[k] = '0';
			temp[i] >>= 1;
			k++;
			j++;
		}
		i++;
	}
	str[k] = '\0';
}

/*
*	ft_ldftoa extracts the binary value of the long float into a string
*/
char	*ft_ldftoa(long double x)
{
	unsigned char		*temp;
	char				*number_in_str;

	number_in_str = (char *)malloc(sizeof(char) * 81);
	if (!number_in_str)
		return (NULL);
	temp = (unsigned char *)(&x);
	fill_nb(number_in_str, temp);
	ft_strrev(number_in_str);
	return (number_in_str);
}

/*
*	sign 	 = 1 bit
*	exponent = 15 bits
*	integer  = 1 bit
*	mantissa = 63 bits
*/
static int	check_nan_inf_l(char *mantissa, char *exp_str)
{
	if (!ft_strcmp("111111111111111", exp_str) && ft_strchr(mantissa, '1'))
		return (1);
	if (!ft_strcmp("111111111111111", exp_str) && !ft_strchr(mantissa, '1'))
		return (-1);
	return (0);
}

static void	handle_nan_inf_l(char **res, char *mantissa, char *exp)
{
	if (check_nan_inf_l(mantissa, exp) == 1)
	{
		res[0] = ft_strdup("nan");
		res[1] = NULL;
	}
	if (check_nan_inf_l(mantissa, exp) == -1)
	{
		res[0] = ft_strdup("inf");
		res[1] = NULL;
	}
}

/*
*	ft_frexpl converts long floating point double to strings
*	@param long double x
*	@return result[] = result[0] and result[1] = decimal strings x.x
*	@return result[2] = sign
*/
char	**ft_frexpl(long double x)
{
	char	*number_in_string;
	char	*mantissa;
	char	exp_bin_in_string[16];
	char	**result;

	exp_bin_in_string[15] = '\0';
	result = (char **)malloc(sizeof(char *) * 3);
	number_in_string = ft_ldftoa(x);
	result[2] = ft_strnew(1);
	ft_strncpy(exp_bin_in_string, number_in_string + 1, 15);
	mantissa = ft_strdup(number_in_string + 16);
	if (!(result) || !(number_in_string) || !(result[2]) || !(mantissa))
		return (NULL);
	if (check_nan_inf_l(mantissa, exp_bin_in_string) != 0)
		handle_nan_inf_l(result, mantissa, exp_bin_in_string);
	else
		calculate_float_l(mantissa, get_exp_l(exp_bin_in_string), result);
	if (number_in_string[0] == '1')
		ft_strcpy(result[2], "-");
	ft_strdel(&number_in_string);
	ft_strdel(&mantissa);
	return (result);
}
