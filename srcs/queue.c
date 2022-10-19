/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue	*init_queue(void)
{
	t_queue	*queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->room = NULL;
	queue->next = NULL;
	queue->queue_item_count = 0;
	return (queue);
}

/*
*	Add to end of the queue
*/
void	insert(t_queue **queue, t_room *room)
{
	t_queue	*temp;
	t_queue	*new;

	new = (t_queue *)malloc(sizeof(t_queue));
	new->room = room;
	new->next = NULL;
	if ((*queue)->room == NULL)
	{
		free(*queue);
		*queue = new;
	}
	else
	{
		if ((*queue)->next == NULL)
			(*queue)->next = new;
		else
		{
			temp = *queue;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new;
		}
	}
	(*queue)->queue_item_count++;
}

/*
*	Remove from front of the queue
*/
void	queue_remove(t_queue **queue)
{
	t_queue	*temp;

	temp = *queue;
	*queue = temp->next;
	free(temp);
}

int	is_queue_empty(t_queue *queue)
{
	if (queue == NULL)
		return (1);
	return (0);
}



/*
*	Check if linked room is the goal, if it is, set it's distance to max
*	int for preventing the exploring algorithm taking illegal shortcuts 
*	through rooms.
*/
void	check_for_goal_new(t_lem_in *lem_in, t_room *temp, t_room *room)
{
	if (temp == lem_in->end_room || temp == lem_in->start_room)
	{
		if (temp != room)
		{
			temp->visited = 1;
			temp->distance = 2147483647;
		}
	}
}


/*
*	Check if the addresses point to the same memory location
*/
int	go_to_linked_rooms(t_lem_in *lem_in, t_queue **queue,
		t_room *room, int distance)
{
	t_room		*neighbor;
	int			i;

	i = 0;
	neighbor = (*queue)->room->neighbors[i];
	while (neighbor)
	{
		// if (neighbor == (*queue)->room)
		// {
		check_for_goal_new(lem_in, neighbor, room);
		if (neighbor->visited == 0)
		{
			neighbor->visited = 1;
			neighbor->distance = ++distance;
			if (neighbor->parent == NULL)
				neighbor->parent = (*queue)->room;
			insert(queue, neighbor);
		}
		// }
		neighbor = (*queue)->room->neighbors[++i];
	}
	return (distance);
}


/*
*	Check if the addresses point to the same memory location
*/
int	go_to_linked_rooms_old(t_lem_in *lem_in, t_queue **queue,
		t_room *room, int distance)
{
	t_link		*temp;
	// int			just_once;

	// just_once = 0;
	temp = lem_in->links;
	while (temp != NULL)
	{
		if (temp->room_1 == (*queue)->room)
		{
			check_for_goal(lem_in, temp, room);
			if (temp->room_2->visited == 0)
			{
				// if (just_once == 0)
				// {
				// 	distance++;
				// 	just_once = 1;
				// }
				temp->room_2->visited = 1;
				temp->room_2->distance = ++distance;
				if (temp->room_2->parent == NULL)
					temp->room_2->parent = temp->room_1;
				insert(queue, temp->room_2);
			}
		}
		temp = temp->next;
	}
	return (distance);
}
