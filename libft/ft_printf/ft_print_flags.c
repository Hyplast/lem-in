/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 01:00:08 by severi            #+#    #+#             */
/*   Updated: 2022/05/22 14:37:15 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_sharp(int c_p, char c)
{
	c_p += print_c('0');
	if (c != 'o')
		c_p += print_c(c);
	return (c_p);
}

int	print_sign(t_flags *flag, int c_p, char **s)
{
	if ((*s)[0] == '-')
	{
		c_p += print_c('-');
		(*s) = (*s) + 1;
		flag->plus = 0;
		flag->space = 0;
	}
	return (c_p);
}

int	is_plus(t_flags *flag, int c_p, char **s, char c)
{
	char	*temp;

	if ((*s)[0] != '-' && (c == 'i' || c == 'd'))
		c_p += print_c('+');
	if ((*s)[0] == '-')
	{
		temp = ft_strsub((*s), 1, ft_strlen((*s)) - 1);
		ft_strcpy((*s), temp);
		ft_strdel(&temp);
	}
	flag->plus = 0;
	return (c_p);
}

int	ft_lookforchar(const char *s, int c)
{
	int	s_len;
	int	i;

	i = -1;
	if (!s)
		return (-1);
	if (ft_strcmp(s, "") == 0)
		return (-1);
	s_len = (int)ft_strlen(s);
	while (s_len >= ++i)
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}
