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

/*
*	Check if the addresses point to the same memory location
*/
void	go_to_linked_rooms(t_lem_in *lem_in, t_queue **queue)
{
	t_link	*temp;
	static int	distance;
	int			just_once;

	just_once = 0;
	temp = lem_in->links;
	while (temp != NULL)
	{
		// ft_printf("temp->room_1 : %p : %s<-> (*queue)->room : %p : %s\n", temp->room_1, temp->room_1->name, (*queue)->room, (*queue)->room->name);
		// ft_printf("sizeof(temp->room_1: %lu\n", sizeof(temp->room_1));
		// ft_printf(sizeof(temp->room_1));
		// ft_printf("\n");
		if ((ft_memcmp(temp->room_1, (*queue)->room, sizeof(temp->room_1)) == 0))
		{
			if (temp->room_2->visited == 0)
			{
				if (just_once == 0)
				{
					distance++;
					just_once = 1;
				}
				temp->room_2->visited = 1;
				temp->room_2->distance = distance;
				// ft_printf("%s\n", temp->room_2->name);
				insert(queue, temp->room_2);
			}
		}
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
		ft_printf("\nStack: %s", (*queue)->room->name);
		queue_remove(queue);
	}
	// while (!lem_in->rooms++)
	// {
	// 	lem_in->rooms->visited = 0;
	// }
	ft_printf("\nlem_in->rooms->name : ");
	ft_printf(lem_in->rooms->name);
	ft_printf("\n");
}

/*
*	Given room x, find the room y that is the shortest distance to x.
*	@return	the room that is the shortest distance to x.
*	@return NULL if no room is found.
*/
t_room	*return_shortest_room(t_lem_in *lem_in, t_room *room_x)
{
	t_room	*shortest_room;
	t_link	*temp_link;
	int		shortest_distance;

	temp_link = lem_in->links;
	shortest_distance = INT32_MAX;
	shortest_room = NULL;
	while (temp_link != NULL)
	{
		if (ft_memcmp(temp_link->room_1, room_x, sizeof(room_x)) == 0)
		{
			if (temp_link->room_2->distance < shortest_distance)
			{
				shortest_distance = temp_link->room_2->distance;
				shortest_room = temp_link->room_2;
			}
		}
		temp_link = temp_link->next;
	}
	return (shortest_room);
}


/*
*	Find the shortest path between start and end rooms.
*/
void	find_shortest_path(t_lem_in *lem_in)
{
	t_room	*room;

	room = lem_in->end_room;
	while (ft_memcmp(room, lem_in->start_room, sizeof(room)) != 0)
	{
		// lem_in_add_move(lem_in, 1, room->name);
		lem_in_add_path(lem_in, room);
		room = return_shortest_room(lem_in, room);
		if (room == NULL)
		{
			handle_error(lem_in, "No path found.");
			exit(-1);
		}
	}
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
	print_rooms(lem_in);

	find_shortest_path(lem_in);
	// ft_printf(queue->room->name);
	

	print_moves(lem_in);
	ft_printf("\n");
}
