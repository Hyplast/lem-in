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
	new->queue_item_count = (*queue)->queue_item_count;
	if ((*queue)->next == NULL)
		*queue = new;
	else
	{
		temp = (*queue)->next;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
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
