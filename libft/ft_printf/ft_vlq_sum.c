/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_sum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:30:02 by severi            #+#    #+#             */
/*   Updated: 2022/03/11 01:30:52 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
*	
*/
static char	compute_char(t_calc *info, char *s1, char *s2, char c)
{
	if (info->len1 >= 0)
		c += s1[info->len1];
	if (info->len2 >= 0)
		c += s2[info->len2];
	if (info->len1 >= 0 && info->len2 >= 0)
		c -= 48;
	info->len1--;
	info->len2--;
	return (c);
}

/*
*	Adds 2 variable lenght que (vlq) -arrays together.
*	48 = 11000	57 = 111001
* 		if ((info->len1 >= 0 && info->len2 >= 0
*				&& ((s1[info->len1] + s2[info->len2] + res[i] - 48) > 57))
*			|| (info->len1 >= 0 && s1[info->len1] + res[i] > 57)
*			|| (info->len2 >= 0 && s2[info->len2] + res[i] > 57))
*		-1 >= 0 && 0 >= 0 && (s1[-1] + s2[0] + res[21845] - 48) > 57
*			-1 >= 0 && s1[-1] + res[21845] > 57
*/
static char	*do_sum(t_calc *info, char *s1, char *s2)
{
	int		i;
	int		hold;
	char	*res;

	res = ft_strnew((size_t)info->max + 2);
	if (!res)
		return (NULL);
	i = info->max;
	while (i > 0)
	{
		hold = 0;
		if ((info->len1 >= 0 && info->len2 >= 0 && ((s1[info->len1]
						+ s2[info->len2] + res[i] - 48) > 57))
			|| (info->len1 >= 0 && s1[info->len1] + res[i] > 57)
			|| (info->len2 >= 0 && s2[info->len2] + res[i] > 57))
		{
			res[i] -= 10;
			hold = 1;
		}
		res[i] = compute_char(info, s1, s2, res[i]);
		res[--i] += hold;
		if (res[0] == 1)
			res[i] += 48;
	}
	return (res);
}

/*
*	Removes leading zeros in a string.
*/
static char	*trim_zero(char *s)
{
	int		i;
	char	*result;

	i = 0;
	while (s[i] == 0)
		i++;
	result = ft_strdup(s + i);
	if (!result)
		return (NULL);
	return (result);
}

/*
*	Adds 2 variable length que (vlq) -arrays together.
*	@return	Sum vlq
*/
char	*vlq_sum(char *s1, char *s2)
{
	char	*temp;
	char	*result;
	t_calc	*info;

	if (!ft_str_isdigit(s1) || !ft_str_isdigit(s2))
		return (NULL);
	info = (t_calc *)malloc(sizeof(t_calc));
	if (!info)
		return (NULL);
	vlq_calculate_info(info, s1, s2);
	info->len1 -= 1;
	info->len2 -= 1;
	temp = do_sum(info, s1, s2);
	result = trim_zero(temp);
	if (!temp || !result)
		return (NULL);
	ft_strdel(&temp);
	free_calc(info);
	return (result);
}
