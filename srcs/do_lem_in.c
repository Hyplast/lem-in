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
*	Bread first traversal to find path lenghts between start and end rooms.
*	Stop if more paths are found than ants exist.
*/
void	bread_first_search(t_lem_in *lem_in, t_queue **queue)
{
	lem_in->start_room->visited = 1;
	insert(queue, lem_in->start_room);
	while (!is_queue_empty(*queue))
	{
		go_to_linked_rooms(lem_in, queue);
		queue_remove(queue);
	}
}

/*
*	Set visited rooms to zero in order to keep count which rooms are 
*	occupied by ants.
*/
void	set_visited_to_zero(t_lem_in *lem_in)
{
	t_path	*path;
	t_path	*temp;
	int		i;

	i = 0;
	path = lem_in->paths[i];
	while (path)
	{
		temp = path;
		while (temp)
		{
			temp->room->visited = 0;
			temp = temp->next_path;
		}
		path = lem_in->paths[++i];
	}
}

void	do_lem_in(t_lem_in *lem_in)
{
	t_queue	*queue;

	queue = init_queue();
	// print_rooms(lem_in);
	// print_links(lem_in);
	// print_ants(lem_in);
	// ft_printf("room_name : %s\n", lem_in->rooms->name);
	// ft_printf("ants : %i\n", lem_in->ants->ant_id);
	// ft_printf("nextl line\n");
	bread_first_search(lem_in, &queue);
	// free(queue);
	find_neighbors(lem_in);
	// ft_printf("\n $£€\n");
	// ft_printf(lem_in->rooms->name);
	// ft_printf("\n");
	// print_rooms(lem_in);
	// ft_printf("START ROOM as t_room->name: %s \n", lem_in->start_room->name);
	// ft_printf("END ROOM as t_room->name: %s \n", lem_in->end_room->name);
	// print_neighbors(lem_in->rooms);
	// print_neighbors(lem_in->rooms->next);
	// print_neighbors(lem_in->rooms->next->next);
	// print_neighbors(lem_in->rooms->next->next->next);
	// print_neighbors(lem_in->rooms->next->next->next->next);
	find_paths(lem_in);
	// ft_printf(queue->room->name);
	print_paths(lem_in);
	set_visited_to_zero(lem_in);
	move_ants(lem_in);
	// print_moves(lem_in);
	ft_printf("\n");
}
