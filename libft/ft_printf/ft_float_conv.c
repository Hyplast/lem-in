/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:04:28 by severi            #+#    #+#             */
/*   Updated: 2022/03/11 01:10:31 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a >= b)
		return (b);
	return (a);
}

void	ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

char	*ft_strrev(char *str)
{
	int		i;
	int		j;

	i = ft_strlen((const char *)str) - 1;
	j = 0;
	while (i >= j)
	{
		ft_swap(&str[i], &str[j]);
		i--;
		j++;
	}
	return (str);
}

int	ft_str_isdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(ft_isdigit(s[i])))
			return (0);
		i++;
	}
	return (1);
}
