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
*	Check if the addresses point to the same memory location
*/
void	go_to_linked_rooms(t_lem_in *lem_in, t_queue **queue, t_room *room)
{
	t_link		*temp;
	static int	distance;
	int			just_once;

	just_once = 0;
	temp = lem_in->links;
	while (temp != NULL)
	{
		if (temp->room_1 == (*queue)->room)
		{
			if (temp->room_2 == lem_in->end_room || temp->room_2 == lem_in->start_room)
			{
				if (temp->room_2 != room)
				{
					temp->room_2->visited = 1;
					temp->room_2->distance = 2147483647;
				}
			}
			if (temp->room_2->visited == 0)
			{
				if (just_once == 0)
				{
					distance++;
					just_once = 1;
				}
				temp->room_2->visited = 1;
				temp->room_2->distance = distance;
				insert(queue, temp->room_2);
			}
		}
		temp = temp->next;
	}
}
