/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:58:14 by severi            #+#    #+#             */
/*   Updated: 2022/06/24 00:42:22 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(int argc, char **argv)
{
	t_lem_in	*lem_in;

	if (argc != 1)
	{
		ft_printf("Usage: ./lem_in \"stdin\"\n");
		if (argv[0] == NULL)
			return (0);
		return (0);
	}
	lem_in = lem_in_init();
	if (!lem_in)
		return (0);
	get_lem_in(lem_in);
	ft_putchar('\n');
	check_lem_in(lem_in);
	do_lem_in(lem_in);
	free_lem_in(lem_in);
	return (0);
}
