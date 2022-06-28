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


void	bread_first_search(t_lem_in *lem_in, t_queue **queue)
{
	// int i;

	insert(queue, lem_in->rooms);
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
	ft_printf((*queue)->room->name);
	ft_printf("\n");

	printf("\n");
}

t_queue	*init_queue(void)
{
	t_queue	*queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->room = NULL;
	queue->next = NULL;
	queue->queue_item_count = 0;
	return (queue);
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
