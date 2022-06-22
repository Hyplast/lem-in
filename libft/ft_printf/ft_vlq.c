/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:22:12 by severi            #+#    #+#             */
/*   Updated: 2022/03/11 01:24:19 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	vlq_initialize(char *vlq, int c, int size)
{
	int	i;

	i = 0;
	while (i < size)
		vlq[i++] = c;
	vlq[i] = '\0';
}

void	vlq_shift_left(char *s, int size)
{
	int		i;
	char	*tmp;

	i = size - 1;
	tmp = ft_strdup(s);
	if (!tmp)
		return ;
	s[i--] = '0';
	while (i >= 0)
	{
		s[i] = tmp[i + 1];
		i--;
	}
	ft_strdel(&tmp);
}

void	vlq_n_shift(char *s, int size, int shifts)
{
	int	i;

	i = 0;
	if (shifts == 0)
		return ;
	while (++i < shifts)
		vlq_shift_left(s, size);
}

void	free_res(char **res)
{
	ft_strdel(&res[0]);
	ft_strdel(&res[1]);
	ft_strdel(&res[2]);
	free(res);
	res = NULL;
}

void	free_calc(t_calc *info)
{
	ft_bzero(info, sizeof(t_calc));
	free(info);
	info = NULL;
}
