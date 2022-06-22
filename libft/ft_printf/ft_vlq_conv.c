/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:27:08 by severi            #+#    #+#             */
/*   Updated: 2022/03/11 01:28:35 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	vlq_calculate_info(t_calc *info, char *s1, char *s2)
{
	info->len1 = ft_strlen(s1);
	info->len2 = ft_strlen(s2);
	info->len1_static = info->len1;
	info->len2_static = info->len2;
	info->max = ft_max(info->len1, info->len2);
	info->min = ft_min(info->len1, info->len2);
	info->sum = info->len1 + info->len2;
	info->ten_dec = 1;
}

void	vlq_char_conv(t_calc *info, char *s1, char *s2)
{
	int	i;

	i = 0;
	while (i <= info->len1)
		s1[i++] -= 48;
	i = 0;
	while (i <= info->len2)
		s2[i++] -= 48;
}

void	vlq_char_conv_rev(char *s, int size)
{
	int	i;

	i = 0;
	while (i < size)
		s[i++] += 48;
}

void	vlq_char_conv_rev_both(t_calc *info, char *s1, char *s2)
{
	int	i;

	i = 0;
	while (i < info->len1_static)
		s1[i++] += 48;
	i = 0;
	while (i < info->len2_static)
		s2[i++] += 48;
}

void	fill_prec(char *result, char *str, int size)
{
	int	j;
	int	i;

	i = 0;
	j = ft_strlen(str);
	while (i <= size && i < j)
	{
		result[i] = str[i];
		i += 1;
	}
	result[i] = '\0';
}
