/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonkarp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue	*init_que(void)
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
void	inse(t_queue **queue, t_room *room)
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
void	queue_rem(t_queue **queue)
{
	t_queue	*temp;

	temp = *queue;
	*queue = temp->next;
	free(temp);
}

int	is_queue_emp(t_queue *queue)
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
void	check_for_go(t_lem_in *lem_in, t_link *temp, t_room *room)
{
	if (temp->room_2 == lem_in->end_room
		|| temp->room_2 == lem_in->start_room)
	{
		if (temp->room_2 != room)
		{
			temp->room_2->visited = 1;
			temp->room_2->distance = 2147483647;
		}
	}
}

/*
*	Check if the addresses point to the same memory location
*/
int	go_to_linked_ro(t_lem_in *lem_in, t_queue **queue,
		t_room *room, int distance)
{
	t_link		*temp;
	int			just_once;

	just_once = 0;
	temp = lem_in->links;
	while (temp != NULL)
	{
		if (temp->room_1 == (*queue)->room)
		{
			check_for_go(lem_in, temp, room);
			if (temp->room_2->visited == 0)
			{
				if (just_once == 0)
				{
					distance++;
					just_once = 1;
				}
				temp->room_2->visited = 1;
				temp->room_2->distance = distance;
				inse(queue, temp->room_2);
			}
		}
		temp = temp->next;
	}
	return (distance);
}


/*
*	Bread first traversal to find path lenghts between start and end rooms.
*/
void	bread_firs(t_lem_in *lem_in, t_queue **queue, t_room *room)
{
	int	distance;

	distance = 0;
	room->visited = 1;
	room->distance = 0;
	inse(queue, room);
	while (!is_queue_emp(*queue))
	{
		distance = go_to_linked_ro(lem_in, queue, room, distance);
		queue_rem(queue);
	}
}




void	edmonkarp(t_lem_in *lem_in)
{
	lem_in->start = 0;
}