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

// /*
// * Add to back of queue
// */
// void	queue_addback(t_queue **queue, t_queue *new)
// {
// 	t_queue	*temp;

// 	if (*alst == NULL)
// 		*alst = new;
// 	else
// 	{
// 		temp = *alst;
// 		while (temp->next != NULL)
// 			temp = temp->next;
// 		temp->next = new;
// 		new->next = NULL;
// 	}
// 	queue->queue_item_count++;
// }
// {
// 	t_queue	*temp;

// 	if (queue == NULL)
// 		queue->room = room;
// 	temp = queue;
// 	while (temp->next != NULL)
// 		temp = temp->next;
// 	temp->next = room;
// 	temp->next->next = NULL;
// 	queue->queue_item_count++;
// }
// /*
// *	Functions to handel questions in lem-in format
// */
// void	insert(t_queue *queue, int data) 
// {
// 	t_queue	*temp;

// 	while (queue->next != NULL)
// 	{
// 		queue
// 		queue = queue->next;
// 		temp = queue;

// 	}
// 	queue->queue[++queue->rear] = data;
//    queue[++rear] = data;
//    queue->queue_item_count++;
// }

// int		remove_data(t_queue *queue)
// {
//    queue->queue_item_count--;
//    return (queue[front++]);
// }

// int		is_queue_empty(t_queue *queue)
// {
//    return queue->queue_item_count == 0;
// }

// int	get_adj_unvisited_rooms(t_lem_in *lem_in, int	room_number)
// {
// 	int	i;

// 	i = 0;
// 	while (i < room_number)
// 	{
// 		if (lem_in->links[room_number][i] == 1 && lstVertices[i]->visited == 0)
// 			return i;
// 		i++;
// 	}
// 	return (-1);
// }

/*
*	check if room is in the list
*/
// int	is_room_in_list(t_lem_in *lem_in, int room_number)
// {
// 	int	i;

// 	i = 0;
// 	while (i < lem_in->room_count)
// 	{
// 		if (lem_in->rooms[i] == room_number)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	go_to_linked_rooms(t_lem_in *lem_in, t_queue **queue)
{
	t_link	*temp;

	temp = lem_in->links;
	while (temp->next != NULL)
	{
		if (temp->room_1 == (*queue)->room && temp->room_1->visited == 0)
			insert(queue, temp->room_1);
		temp->room_1->visited = 1;
		temp = temp->next;
	}
}

/*
*	Bread first traversal to find the shortest path
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
		queue_remove(queue);

	}
	while(!lem_in->rooms++)
	{
		lem_in->rooms->visited = 0;
	}

	// lem_in->state[lem_in->start] = waiting;
	// while (!is_queue_empty(lem_in))
	// {
	// 	int v = remove_data();
	// 	lem_in->state[v] = visited;
	// 	printf("%c ", v + 'A');
	// 	for (i = 0; i < lem_io->rooms_count; i++)
	// 	{
	// 		if (lem_in->links[v][i] == 1 && lem_in->state[i] == initial)
	// 		{
	// 			insert(i);
	// 			lem_in->state[i] = waiting;
	// 		}
	// 	}
	// }
	ft_printf("\n");
	ft_printf(lem_in->rooms->name);
	ft_printf("\n");
}


void	do_lem_in(t_lem_in *lem_in)
{
	//queue variables

	// int	*queue;
	// int rear = -1;
	// int front = 0;			
	//int queueItemCount = 0;		//lem_in->rooms_count	
	t_queue	*queue;

	queue = init_queue();
	print_rooms(lem_in);
	print_links(lem_in);
	print_ants(lem_in);
	// print_moves(lem_in);
		// while ()
	ft_printf("room_name : %s\n" ,lem_in->rooms->name);
	ft_printf("ants : %i\n" ,lem_in->ants->ant_id);
	ft_printf("nextl line\n");
	bread_first_search(lem_in, &queue);
ft_printf("\n");
	ft_printf(lem_in->rooms->name);
ft_printf("\n");
	ft_printf(queue->room->name);
	ft_printf("\n");
}
