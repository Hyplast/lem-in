/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	go_to_linked_rooms(t_lem_in *lem_in, t_queue **queue)
{
	t_link	*temp;

	temp = lem_in->links;
	while (temp->next != NULL)
	{
		if ((ft_memcmp(temp->room_1, (*queue)->room, 8) == 0) && temp->room_1->visited == 0)
			insert(queue, temp->room_1);
		temp->room_1->visited = 1;
		temp = temp->next;
	}
}

/*
*	Bread first traversal to find path lenghts between start and end rooms.
*	Stop if more paths are found than ants exist.
*/
void	bread_first_search(t_lem_in *lem_in, t_queue **queue)
{
	lem_in->start_room->visited = 1;
	insert(queue, lem_in->start_room);
	ft_printf("\nStack start: ");
	ft_printf((*queue)->room->name);
	ft_printf("\n");
	while (!is_queue_empty(*queue))
	{
		go_to_linked_rooms(lem_in, queue);
		ft_printf("\nStack: ");
		ft_printf((*queue)->room->name);
		queue_remove(queue);
	}
	// while (!lem_in->rooms++)
	// {
	// 	lem_in->rooms->visited = 0;
	// }
	ft_printf("\n");
	ft_printf(lem_in->rooms->name);
	ft_printf("\n");
}

void	do_lem_in(t_lem_in *lem_in)
{
	t_queue	*queue;

	queue = init_queue();
	print_rooms(lem_in);
	print_links(lem_in);
	print_ants(lem_in);
	ft_printf("room_name : %s\n", lem_in->rooms->name);
	ft_printf("ants : %i\n", lem_in->ants->ant_id);
	ft_printf("nextl line\n");
	bread_first_search(lem_in, &queue);
	ft_printf("\n");
	ft_printf(lem_in->rooms->name);
	ft_printf("\n");
	ft_printf(queue->room->name);
	ft_printf("\n");
}
