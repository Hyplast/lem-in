/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floatl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:14:03 by severi            #+#    #+#             */
/*   Updated: 2022/06/06 10:46:30 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	is_neg_exp_l(char *mantissa, int exp, char **result)
{
	char	*right;
	int		i;
	int		j;

	i = 0;
	j = 0;
	exp = -exp;
	right = ft_strnew(63 + exp);
	if (!right)
		return ;
	while (i < exp - 1)
		right[i++] = '0';
	while (i < 63)
	{
		if (mantissa[j] == '0' || mantissa[j] == '1')
			right[i++] = mantissa[j++];
	}
	right[i] = '\0';
	result[0] = ft_strdup("0");
	result[1] = ft_bin_to_dec(right);
	if (!result[0] || !result[1])
		return ;
	ft_strdel(&right);
}

static void	is_big_exp_l(char *mantissa, int exp, char **res)
{
	char	*left;
	int		i;

	i = 0;
	left = ft_strnew(exp + 1);
	if (!left)
		return ;
	if (!(ft_strncat(left, mantissa, exp + 1)))
		return ;
	while (left[i] == '0' || left[i] == '1')
		i++;
	while (i < exp + 1)
		left[i++] = '0';
	res[0] = ft_bin_to_int(left);
	res[1] = ft_strdup("0");
	if (!res[0] || !res[1])
		return ;
	ft_strdel(&left);
}

static void	is_pos_exp_l(char *mantissa, int exp, char **res)
{
	char	*left;
	char	*right;

	if (exp > 64)
	{
		is_big_exp_l(mantissa, exp, res);
		return ;
	}
	left = ft_strnew(exp + 1);
	right = ft_strnew(63 - exp);
	if (!left || !right
		|| !(ft_strncat(left, mantissa, exp + 1))
		|| !(ft_strcpy(right, mantissa + exp + 1)))
		return ;
	res[0] = ft_bin_to_int(left);
	res[1] = ft_bin_to_dec(right);
	if (!res[0] || !res[1])
		return ;
	ft_strdel(&left);
	ft_strdel(&right);
}

void	calculate_float_l(char *mantissa, int exp, char **res)
{
	if (exp < 0)
		is_neg_exp_l(mantissa, exp, res);
	else
		is_pos_exp_l(mantissa, exp, res);
}

int	get_exp_l(char *exp_str)
{
	int	number;
	int	i;
	int	j;

	j = 14;
	i = 0;
	number = 0;
	while (exp_str[i] != '\0')
	{
		if (exp_str[i] == '1')
			number = number + power_of_two(j);
		i++;
		j--;
	}
	number -= 16383;
	return (number);
}
