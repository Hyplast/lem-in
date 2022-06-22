/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frexp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:00:08 by severi            #+#    #+#             */
/*   Updated: 2022/06/06 11:37:24 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
*	ft_dftoa converts binary of the float into a string
*/
char	*ft_dftoa(double x)
{
	int					i;
	unsigned long		temp;
	char				*binary_in_string;

	i = 0;
	binary_in_string = (char *)malloc(sizeof(char) * 65);
	if (!binary_in_string)
		return (NULL);
	temp = *(unsigned long *)(&x);
	while (i <= 63)
	{
		if (temp & 1)
			binary_in_string[i] = '1';
		else
			binary_in_string[i] = '0';
		temp >>= 1;
		i++;
	}
	binary_in_string[i] = '\0';
	ft_strrev(binary_in_string);
	return (binary_in_string);
}

/*
*	check_nan_inf checks if the number entered exists and is not infinite
*	and returns 1 after printing "nan" or "inf" if it is
*/
static int	check_nan_inf(char *mantissa, char *exp_str)
{
	if (!ft_strcmp("11111111111", exp_str) && ft_strchr(mantissa, '1'))
		return (1);
	if (!ft_strcmp("11111111111", exp_str) && !ft_strchr(mantissa, '1'))
		return (-1);
	return (0);
}

static void	handle_nan_inf(char **res, char *mantissa, char *exp)
{
	if (check_nan_inf(mantissa, exp) == 1)
	{
		res[0] = ft_strdup("nan");
		res[1] = NULL;
	}
	if (check_nan_inf(mantissa, exp) == -1)
	{
		res[0] = ft_strdup("inf");
		res[1] = NULL;
	}
}

/*
*	ft_frexp converts floating point double to strings
*	@param double x
*	@return result[] = result[0] and result[1] = decimal strings x.x
*	@return result[2] = sign
*/
char	**ft_frexp(double x)
{
	char	*number_in_string;
	char	*mantissa;
	char	exp_bin_in_string[12];
	char	**result;

	exp_bin_in_string[11] = '\0';
	result = (char **)malloc(sizeof(char *) * 3);
	number_in_string = ft_dftoa(x);
	result[2] = ft_strnew(1);
	ft_strncpy(exp_bin_in_string, number_in_string + 1, 11);
	mantissa = ft_strdup(number_in_string + 12);
	if (!(result) || !(number_in_string) || !(result[2]) || !(mantissa))
		return (NULL);
	if (check_nan_inf(mantissa, exp_bin_in_string) != 0)
		handle_nan_inf(result, mantissa, exp_bin_in_string);
	else
		calculate_float(mantissa, get_exp(exp_bin_in_string), result);
	if (number_in_string[0] == '1')
		ft_strcpy(result[2], "-");
	ft_strdel(&mantissa);
	ft_strdel(&number_in_string);
	return (result);
}
