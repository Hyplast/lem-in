/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lem_in_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:58:14 by severi            #+#    #+#             */
/*   Updated: 2022/06/24 00:42:22 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	Check if string is digits
*/
int	is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_for_integer(char *str)
{
	int	i;

	i = is_digits(str);
	if (i == 1)
		return (ft_atoi(str));
	ft_putstr("ERROR coordinates are not digits\n");
	exit(1);
}

void	handle_room_print(char *str)
{
	if (str[0] == '#')
	{
		if (str[1])
		{
			if (str[1] == '#')
				return ;
		}
	}
	ft_putstr(str);
	ft_putchar('\n');
}

void	handle_ant_print(t_lem_in *lem_in, char *buf)
{
	lem_in->ants_count = ft_atoi(buf);
	ft_putnbr(lem_in->ants_count);
	ft_putchar('\n');
}
