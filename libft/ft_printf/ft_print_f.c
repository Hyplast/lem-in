/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 01:47:10 by severi            #+#    #+#             */
/*   Updated: 2022/04/08 01:00:12 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	free_double_char(char **s)
{
	if (s)
	{
		if (*s)
		{
			ft_strdel(&s[0]);
			ft_strdel(&s[1]);
			ft_strdel(&s[2]);
		}
		free(*s);
		*s = NULL;
		free(s);
		s = NULL;
	}
}

static void	combine_chars(char **str)
{
	char	*temp;
	char	*result;
	char	*sign;

	if (*str[2] == '-')
	{
		sign = ft_strjoin("-", str[0]);
		temp = ft_strjoin(sign, ".");
		ft_strdel(&sign);
	}
	else
		temp = ft_strjoin(str[0], ".");
	result = ft_strjoin(temp, str[1]);
	ft_strdel(&str[0]);
	ft_strdel(&str[1]);
	ft_strdel(&str[2]);
	*str = ft_strdup(result);
	ft_strdel(&result);
	ft_strdel(&temp);
}

static int	print_nan_inf(t_flags *flags, int chars_printed, char **str)
{
	char	*sign;
	char	*temp;

	if (str[2][0] == '-' && ft_strcmp(str[0], "inf") == 0)
	{
		sign = ft_strjoin("-", str[0]);
		temp = ft_strdup(sign);
		ft_strdel(&sign);
	}
	else
		temp = ft_strdup(str[0]);
	chars_printed = print_before(flags, chars_printed, temp, ' ');
	ft_strdel(&temp);
	free_double_char(str);
	return (chars_printed);
}

int	print_llong(t_flags *flag_s, va_list ap, int chars_printed)
{
	long double	ld;
	char		**s;
	int			decimals;

	ld = (long double) va_arg(ap, long double);
	s = ft_frexpl(ld);
	if (ft_strcmp(s[0], "nan") == 0 || ft_strcmp(s[0], "inf") == 0)
		return (print_nan_inf(flag_s, chars_printed, s));
	if (ft_strcmp(s[1], "") == 0 && ft_strlen(s[1]) <= 1)
		ft_add_zeros(&s[1], flag_s->prec - ft_strlen(s[1]));
	ft_round(s, flag_s->prec);
	decimals = ft_strlen(s[1]);
	if (decimals < flag_s->prec)
		ft_add_zeros(&s[1], flag_s->prec - decimals);
	if (s[1][0] == '0' && ft_strlen(s[1]) == 1)
		ft_add_zeros(&s[1], flag_s->prec - ft_strlen(s[1]));
	if (decimals != 0)
	{
		combine_chars(s);
		chars_printed = print_before(flag_s, chars_printed, *s, ' ');
	}
	else
		chars_printed = print_before(flag_s, chars_printed, s[0], ' ');
	free_double_char(s);
	return (chars_printed);
}

int	print_f(t_flags *flag_s, va_list ap, int chars_printed)
{
	double		f;
	char		**s;
	int			decimals;

	if (flag_s->spec == 3)
		return (print_llong(flag_s, ap, chars_printed));
	f = va_arg(ap, double);
	s = ft_frexp(f);
	if (ft_strcmp(s[0], "nan") == 0 || ft_strcmp(s[0], "inf") == 0)
		return (print_nan_inf(flag_s, chars_printed, s));
	ft_round(s, flag_s->prec);
	decimals = ft_strlen(s[1]);
	if (decimals < flag_s->prec)
		ft_add_zeros(&s[1], flag_s->prec - decimals);
	if (s[1][0] == '0' && ft_strlen(s[1]) == 1)
		ft_add_zeros(&s[1], flag_s->prec - ft_strlen(s[1]));
	if (decimals != 0)
	{
		combine_chars(s);
		chars_printed = print_before(flag_s, chars_printed, *s, ' ');
	}
	else
		chars_printed = print_before(flag_s, chars_printed, s[0], ' ');
	free_double_char(s);
	return (chars_printed);
}
