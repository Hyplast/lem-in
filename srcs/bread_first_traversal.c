/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bread_first_traversal.c                            :+:      :+:    :+:   */
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
*/
void	bread_first_search(t_lem_in *lem_in, t_queue **queue, t_room *room)
{
	room->visited = 1;
	insert(queue, room);
	while (!is_queue_empty(*queue))
	{
		go_to_linked_rooms(lem_in, queue);
		queue_remove(queue);
	}
}

/*
*	Set visited rooms to zero.
*/
void	set_all_visited_to_zero(t_lem_in *lem_in)
{
	t_room	*temp;

	temp = lem_in->rooms;
	while (temp)
	{
		temp->visited = 0;
		temp = temp->next;
	}
}

/*
*	Set visited rooms in paths to zero in order to keep count which rooms are 
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
