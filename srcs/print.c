/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	handle_error(t_lem_in *lem_in, char *error_msg)
{
	ft_putstr(error_msg);
	free_lem_in(lem_in);
	return (0);
}

void	print_rooms(t_lem_in *lem_in)
{
	t_room	*temp;
	int		len;

	len = 0;
	temp = lem_in->rooms;
	while (temp != NULL)
	{
		ft_printf("room_name : %10s ", temp->name);
		ft_printf(" room_coord : %i %i", temp->x, temp->y);
		ft_printf(" room_distance : %i\n", temp->distance);
		len++;
		temp = temp->next;
	}
	ft_printf("amount of rooms: %i\n", len);
}

void	print_links(t_lem_in *lem_in)
{
	t_link	*temp;

	temp = lem_in->links;
	while (temp != NULL)
	{
		ft_printf("room      : %10s  linked with %10s\n",
			temp->room_1->name, temp->room_2->name);
		temp = temp->next;
	}
}

void	print_moves(t_lem_in *lem_in)
{
	t_move	*temp;

	temp = lem_in->moves;
	while (temp != NULL)
	{
		ft_printf("L%i-%s", temp->ant_id, temp->room_name);
		temp = temp->next;
	}
	ft_printf("\n");
}

void	print_ants(t_lem_in *lem_in)
{
	t_ant	*temp;

	temp = lem_in->ants;
	while (temp != NULL)
	{
		ft_printf("ant_id : %i room_name : %s\n",
			temp->ant_id, temp->room->name);
		temp = temp->next;
	}
}
