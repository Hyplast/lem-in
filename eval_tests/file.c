#include "lem_in.h"


void	do_lem_in(t_lem_in *lem_in)
{
	char	*room_start;
	char	*room_end;
	int		x;
	int		y;

	x = 23;
	y = 3;

	room_start = ft_strdup("start");
	room_end = ft_strdup("end");

	lem_in_add_room(lem_in, room_start, x, y);
	lem_in_add_room(lem_in, "middle", x, y);
	lem_in_add_room(lem_in, room_end, x, y);

	lem_in_add_link(lem_in, room_start, "middle");
	lem_in_add_link(lem_in, room_end, "middle");
	lem_in_add_link(lem_in, room_start, room_end);

	int i;
	i = 1;
	while (i++ < 10)
		lem_in_add_ant(lem_in, i, room_start);


	lem_in_add_move(lem_in, 1, room_end);
	lem_in_add_move(lem_in, 2, room_end);
	lem_in_add_move(lem_in, 3, "middle");


	print_rooms(lem_in);
	print_links(lem_in);
	print_moves(lem_in);
		// while ()
	ft_printf("room_name : %s\n" ,lem_in->rooms->name);
	ft_printf("ants : %i\n" ,lem_in->ants->ant_id);
}


/* Read stdout from argv[1] and parse it */

void	print_lem_in(t_lem_in *lem_in)
{
	int i;

	i = 0;
	while (lem_in->rooms[i].name)
	{
		ft_putstr(lem_in->rooms[i].name);
		ft_putstr(" ");
		ft_putnbr(lem_in->rooms[i].x);
		ft_putstr(" ");
		ft_putnbr(lem_in->rooms[i].y);
		ft_putstr("\n");
		i++;
	}
	i = 0;
	while (lem_in->links[i])
	{
		ft_putstr(lem_in->links[i]);
		ft_putstr("\n");
		i++;
	}
	i = 0;
	while (lem_in->ants[i])
	{
		ft_putstr(lem_in->ants[i]);
		ft_putstr("\n");
		i++;
	}
	print_moves(lem_in);
}

void	print_route(t_lem_in *lem_in, int ant_id, int *route)
{
	int i;

	i = 0;
	while (route[i])
	{
		print_move(lem_in, ant_id, lem_in->rooms[route[i]].name);
		i++;
	}
}

void	print_moves(t_lem_in *lem_in)
{
	int i;

	i = 0;
	while (lem_in->moves[i])
	{
		print_route(lem_in, i + 1, lem_in->moves[i]);
		ft_putstr("\n");
		i++;
	}
}

/*
* Sort the array of void * pointers in ascending order.
* The array must be terminated by a NULL pointer.
*/
void	sort_array(void **array)
{
	int		i;
	int		j;
	void	*temp;

	i = 0;
	while (array[i] != NULL)
	{
		j = i + 1;
		while (array[j] != NULL)
		{
			if (ft_strcmp((char *)array[i], (char *)array[j]) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/*
* Sort the array of void * pointers in descending order.
* The array must be terminated by a NULL pointer.
*/
void	sort_array_desc(void **array)
{
	int		i;
	int		j;
	void	*temp;

	i = 0;
	while (array[i] != NULL)
	{
		j = i + 1;
		while (array[j] != NULL)
		{
			if (ft_strcmp((char *)array[i], (char *)array[j]) < 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}


/*
*	Check if room is already in the list
*/
int		is_room_in_list(t_lem_in *lem_in, char *room_name)
{
	t_room	*temp;

	temp = lem_in->rooms;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, room_name) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

/*
*	Check if room is valid
*/
int		is_room_valid(char *line)
{
	char	**temp;
	int		i;
	int		len;

	temp = ft_strsplit(line, ' ');
	len = lenght_of_array(temp);
	if (len != 3)
		return (0);
	i = 0;
	while (i < len)
	{
		if (ft_isprint(temp[i][0]) == 0)
			return (0);
		i++;
	}
	free_array(temp);
	return (1);
}

/*
*	Check if link is valid
*/
int		is_link_valid(t_lem_in *lem_in, char *line)
{
	char	**temp;
	int		i;
	int		len;

	temp = ft_strsplit(line, '-');
	len = lenght_of_array(temp);
	if (len != 2)
		return (0);
	i = 0;
	while (i < len)
	{
		if (is_room_in_list(lem_in, temp[i]) == 0)
			return (0);
		i++;
	}
	free_array(temp);
	return (1);
}


/*
*    Calculate the distance between two rooms
*/




 
void BFS(int v)
{
	int i;
	insert_queue(v);
	state[v] = waiting;
	while(!isEmpty_queue())
	{
		v = delete_queue( );
		printf("%d ",v);
		state[v] = visited;
		for(i=0; i<n; i++)
		{
			if(adj[v][i] == 1 && state[i] == initial)
			{
				insert_queue(i);
				state[i] = waiting;
			}
		}
	}
	printf("\n");
}
 
void insert_queue(int vertex)
{
	if(rear == MAX-1)
		printf("Queue Overflow\n");
	else
	{
		if(front == -1)
			front = 0;
		rear = rear + 1;
		queue[rear] = vertex ;
	}
}
 
int isEmpty_queue()
{
	if(front == -1 || front > rear)
		return 1;
	else
		return 0;
}

int delete_queue()
{
	int delete_item;
	if(front == -1 || front > rear)
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	delete_item = queue[front];
	front = front+1;
	return delete_item;
}

/* Reverse the order of the elements in the array 
*  of void * pointers.
*  The array must be terminated by a NULL pointer.
*/
void	reverse_array(void **array)
{
	void	*temp;
	int		i;

	i = 0;
	while (array[i] != NULL)
	{
		temp = array[i];
		array[i] = array[i + 1];
		array[i + 1] = temp;
		i++;
	}
}



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
	//queue variables

	// int	*queue;
	// int rear = -1;
	// int front = 0;			
	//int queueItemCount = 0;		//lem_in->rooms_count	



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