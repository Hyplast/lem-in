/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_lem_in(t_lem_in *lem_in)
{
	free(lem_in->rooms);
	free(lem_in->links);
	free(lem_in->ants);
	free(lem_in->moves);
	free(lem_in);
}

int handle_error(t_lem_in *lem_in, char *error_msg)
{
	ft_putstr(error_msg);
	free_lem_in(lem_in);
	return (0);
}
	




void	do_lem_in(t_lem_in *lem_in)
{
	char	*room_start;
	char	*room_end;
	int		x;
	int		y;

	x = 23;
	y = 3;

	room_start = ft_strdup("start");
	room_end = ft_strdup("end");

	lem_in_add_room(lem_in, room_start, x, y);
	lem_in_add_room(lem_in, "middle", x, y);
	lem_in_add_room(lem_in, room_end, x, y);

	lem_in_add_link(lem_in, room_start, "middle");
	lem_in_add_link(lem_in, room_end, "middle");
	lem_in_add_link(lem_in, room_start, room_end);

	int i;
	i = 1;
	while (i++ < 10)
		lem_in_add_ant(lem_in, i, room_start);


	t_room	*temp;
	int	len;

	len = 0;
	temp = lem_in->rooms;
	while (temp != NULL)
	{
		ft_printf("room_name : %10s " ,temp->name);
		ft_printf(" room_coord : %i %i\n" ,temp->x, temp->y);
		len++;
		temp = temp->next;
	}

	t_link	*l_temp;

	l_temp = lem_in->links;
	while (l_temp != NULL)
	{
		ft_printf("room      : %10s  linked with %10s\n" ,l_temp->name1, l_temp->name2);
		l_temp = l_temp->next;
	}


	ft_printf("amount of rooms: %i\n" , len);
	// while ()
	ft_printf("room_name : %s\n" ,lem_in->rooms->name);
	ft_printf("ants : %i\n" ,lem_in->ants->ant_id);
}


int	main(int argc, char **argv)
{
	t_lem_in	*lem_in;

	if (argc != 1)
	{
		ft_printf("Usage: ./lem_in\n");
		return (0);
	}
	else if (argc == 2)
	{
		if (ft_strncmp("-v", argv[2], 2))
		{
			ft_printf("Using visualizer\n");
			return (0);
		}
	}
	lem_in = lem_in_init();
	if (!lem_in)
		return (0);
	do_lem_in(lem_in);
	return (0);
}
