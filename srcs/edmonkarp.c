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
				temp->room_2->parent = temp->room_1;
				inse(queue, temp->room_2);
			}
		}
		temp = temp->next;
	}
	return (distance);
}


// void	print_parents(t_lem_in *lem_in)
// {
// 	t_room *ending;

// 	ending = lem_in->end_room;
	
// }

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


// void	update_augment_values()
// {
// 	t_queue	*queue;

// 	queue = init_queue();
// 	bread_firs(lem_in, &queue, lem_in->start_room);

// }

/*
*	Set visited rooms in a path x.
*/
void	set_path_to_visited(t_path *path, int x)
{
	t_path	*temp;

	temp = path;
	while (temp)
	{
		temp->room->visited = x;
		temp = temp->next_path;
	}
}

t_node	*find_a_node(t_lem_in *lem_in, t_room *room)
{
	t_node	*temp;

	temp = lem_in->nodes;
	while (temp)
	{
		if (temp->room == room)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/*
*	Given room x, find the room y that is the shortest distance to x.
*	@return	the room that is the shortest distance to x.
*	@return NULL if no room is found. 
*/
t_room	*return_the_shortest_room(t_room *start, t_room *room)
{
	t_room	*temp;
	t_room	*shortest_room;
	int		shortest_distance;
	int		i;

	i = 0;
	shortest_room = NULL;
	temp = room->neighbors[i];
	shortest_distance = 2147483647;
	while (temp != NULL)
	{
		if (temp->distance < shortest_distance)
		{
			if (temp != start && temp->visited != 3)
			{
				shortest_distance = temp->distance;
				shortest_room = temp;
			}
		}
		temp = room->neighbors[++i];
	}
	return (shortest_room);
}

/*
*	Find the shortest path between start and end rooms different than last path.
*	@return	the shortest path between start and end rooms.
*	@return NULL if no path is found.
*/
t_path	*create_the_path(t_lem_in *lem_in, t_room *room, t_room *start, t_room *end)
{
	t_path	*path;

	path = lem_in_add_new_path(end);
	while (room != end)
	{
		lem_in_add_to_path(&path, room);
		room = return_the_shortest_room(start, room);
		if (room->visited == 2)
		{
			room->visited = 3;
			lem_in_add_to_path(&path, room);
			room = room->parent;
		}
		if (room == NULL)
		{
			handle_error(lem_in, "ERROR no path found.");
			exit(-1);
		}
	}
	lem_in_add_to_path(&path, start);
	return (path);
}

/*
*	Find the shortest path between start and given room.
*	Add it to the path list.
*	@return void
*/
void	find_the_paths(t_lem_in *lem_in, t_room *room, t_room *start, t_room *end)
{
	t_path	**paths;
	t_path	*path;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (lem_in->paths != NULL)
	{
		while (lem_in->paths[len] != NULL)
			len++;
	}
	paths = (t_path **)malloc(sizeof(t_path *) * ((size_t)len + 1 + 1));
	path = create_the_path(lem_in, room, start, end);
	while (i < len)
	{
		paths[i] = lem_in->paths[i];
		i++;
	}
	paths[len] = path;
	paths[len + 1] = NULL;
	free(lem_in->paths);
	lem_in->paths = paths;
}

/*
*	Given room x, find the room y that is the shortest distance to x.
*	@return	the room that is the shortest distance to x.
*	@return NULL if no room is found. 
*/
t_room	*return_shortest_node(t_room *start, t_room *room)
{
	t_room	*temp;
	t_room	*shortest_room;
	int		shortest_distance;
	int		i;

	i = 0;
	shortest_room = NULL;
	temp = room->neighbors[i];
	shortest_distance = 2147483647;
	while (temp != NULL)
	{
		if (temp->distance < shortest_distance)
		{
			if (temp != start && temp->visited != 3)
			{
				shortest_distance = temp->distance;
				shortest_room = temp;
			}
		}
		temp = room->neighbors[++i];
	}
	return (shortest_room);
}

void	find_that_path(t_lem_in *lem_in, t_room *room)
{
	t_room	*neighbor;
	t_room	*prev;
	t_node	*node;
	int		i;

	i = 0;
	prev = room;
	neighbor = room->neighbors[i];
	while (neighbor)
	{
		node = find_a_node(lem_in, neighbor);
		if (!node->in)
			node->in = prev;
		
		neighbor = room->neighbors[++i];
	}

}


void	init_node(t_lem_in *lem_in, t_room *room)
{
	t_node	*node;

	node = (t_node*)malloc(sizeof(t_node));
	node->room = room;
	node->in = NULL;
	node->out = NULL;
	node->in_visited = 0;
	node->out_visited = 0;
	node->next = lem_in->nodes;
	lem_in->nodes = node;
}

void	init_all_nodes(t_lem_in *lem_in)
{
	t_room	*room;

	room = lem_in->rooms;
	while (room)
	{
		init_node(lem_in, room);
		room = room->next;
	}
}

void	set_nodes_for_path(t_lem_in *lem_in, t_path *path)
{
	t_path	*temp;
	t_node	*prev;
	t_node	*node;

	temp = path;
	init_all_nodes(lem_in);
	node = find_a_node(lem_in, temp->room);
	prev = node;
	temp = temp->next_path;
	node->out = temp->room;
	while (temp)
	{
		node = find_a_node(lem_in, temp->room);
		node->in = prev->room;
		prev = node;
		temp = temp->next_path;
		if (temp)
			node->out = temp->room;
	}
}

void	edmonkarp(t_lem_in *lem_in)
{
	// t_path	*path;
	t_room	*room;
	int		i;

	i = 0;
	set_all_visited_to_zero(lem_in);
	set_nodes_for_path(lem_in, lem_in->paths[0]);
	// set_path_to_visited(lem_in->paths[0], 2);
	// lem_in->start_room->visited = 3;
	// path = lem_in->paths[1];
	room = lem_in->start_room->neighbors[++i];
	while (room)
	{
		find_that_path(lem_in, room);
		// find_the_paths(lem_in, room, lem_in->start_room,
			// lem_in->end_room);
		
		// return_shortest_room(start, room)
		
		room = lem_in->start_room->neighbors[++i];
	}

}

