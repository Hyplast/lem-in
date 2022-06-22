/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:37:50 by severi            #+#    #+#             */
/*   Updated: 2022/04/08 00:18:28 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnchar(const char *s, size_t n)
{
	int	i;

	i = 0;
	while (n-- > 0 && *s != '\0')
	{	
		ft_putchar(*s++);
		i++;
	}
	return (i);
}

int	ft_putcx(char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{	
		ft_putchar(c);
		i++;
	}
	return (i);
}

void	fix_overrides(t_flags *flag_s, const char c)
{
	if (flag_s->prec != -1)
		flag_s->zero = 0;
	if (c == 'f' && flag_s->prec == -1)
		flag_s->prec = 6;
	if ((c == 'd' || c == 'i') && flag_s->prec == -1)
		flag_s->prec = 1;
	if ((c == 'o' || c == 'u' || c == 'x' || c == 'X') && flag_s->prec == -1)
		flag_s->prec = 1;
	if (flag_s->plus == 1)
		flag_s->space = 0;
	if (flag_s->minus == 1)
		flag_s->zero = 0;
}

void	init_flags(t_flags *flag_s, const char *flags)
{
	flag_s->len = ft_strlen(flags) - 1;
	flag_s->spec = 0;
	flag_s->width = 0;
	flag_s->prec = -1;
	flag_s->sharp = 0;
	flag_s->minus = 0;
	flag_s->plus = 0;
	flag_s->space = 0;
	flag_s->zero = 0;
}

void	free_flags(t_flags *flags)
{
	ft_bzero(flags, sizeof(t_flags));
	free(flags);
	flags = NULL;
}
