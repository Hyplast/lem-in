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

t_node	*find_a_node(t_lem_in *lem_in, t_room *room)
{
	t_node	*temp;

	temp = lem_in->nodes;
	if (room == NULL)
		return (NULL);
	while (temp)
	{
		if (temp->room == room)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}


void	print_node_paths(t_lem_in *lem_in)
{
	t_node	*node;
	t_room	*room;
	int		i;

	i = 0;
	room = lem_in->start_room->neighbors[i];
	while (room)
	{
		ft_printf("#%s#->\n", lem_in->nodes->room->name);
		node = find_a_node(lem_in, room);
		while (node)
		{
			ft_printf("#%s#:->", node->room->name);
			if (node->out && node->in)
				ft_printf("out: %s, in: %s ", node->out->room->name, node->in->room->name);
			ft_printf("node->in_vis: %d, ->out_vis: %d\n", node->in_visited, node->out_visited);
			node = node->out;
		}
		ft_putchar('\n');
		room = lem_in->start_room->neighbors[++i];
	}
}


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

// /*
// *	Given node x, find the node y that is the shortest distance to end.
// *	@return	the room that is the shortest distance to x.
// *	@return NULL if no room is found. 
// */
// t_node	*return_shortest_node(t_lem_in *lem_in, t_node *node, int flow)
// {
// 	t_node	*temp;
// 	t_node	*shortest_node;
// 	int		shortest_distance;
// 	int		i;

// 	i = 0;
// 	shortest_node = NULL;
// 	temp = find_a_node(lem_in, node->room->neighbors[i]);
// 	shortest_distance = 2147483647;
// 	while (temp != NULL)
// 	{
// 		if (temp->out == NULL && temp->in == NULL)
// 		{
// 			shortest_distance = temp->room->distance;
// 			shortest_node = temp;
// 		}
// 		if (temp->room->distance < shortest_distance)
// 		{
// 			if (temp->in_visited != 1)
// 			{
// 				if (flow == 1 && temp->room != lem_in->end_room)
// 				{
// 					if (temp->out == NULL && temp->in == NULL)
// 					{
// 						shortest_distance = temp->room->distance;
// 						shortest_node = temp;
// 					}
// 				}
// 				else
// 				{
// 					shortest_distance = temp->room->distance;
// 					shortest_node = temp;
// 				}
// 			}
// 		}
// 		temp = find_a_node(lem_in, node->room->neighbors[++i]);
// 	}
// 	return (shortest_node);
// }


t_node	*find_neighbors_with_flow(t_lem_in *lem_in, t_node *node, t_node *shortest_node, int shortest_distance)
{
	t_node	*temp;
	int		i;

	i = 0;
	temp = find_a_node(lem_in, node->room->neighbors[i]);
	while (temp != NULL)
	{
		if (temp->in_visited != 1)
		{
			if (temp->room->distance < shortest_distance)
			{
				shortest_distance = temp->room->distance;
				shortest_node = temp;
			}
		}
		temp = find_a_node(lem_in, node->room->neighbors[++i]);
	}
	return (shortest_node);
}

/*
*	Given node x, find the node y that is the shortest distance to end.
*	@return	the room that is the shortest distance to x.
*	@return NULL if no room is found. 
*/
t_node	*return_shortest_node(t_lem_in *lem_in, t_node *node)
{
	t_node	*temp;
	t_node	*shortest_node;
	int		shortest_distance;
	int		i;

	i = 0;
	shortest_node = NULL;
	temp = find_a_node(lem_in, node->room->neighbors[i]);
	shortest_distance = 2147483647;
	while (temp != NULL)
	{
		if (temp->room == lem_in->end_room)
			return (temp);
		if (temp->in_visited != 1 && temp->out == NULL && temp->in == NULL)
		{
			if (temp->room->distance < shortest_distance)
			{
				shortest_distance = temp->room->distance;
				shortest_node = temp;
			}
		}
		temp = find_a_node(lem_in, node->room->neighbors[++i]);
	}
	// if (shortest_node == NULL)
	shortest_node = find_neighbors_with_flow(lem_in, node, shortest_node, shortest_distance);
	return (shortest_node);
}

void	case_travel_upstream(t_node *node, t_node *prev)
{
	if (prev->out != NULL)
		prev->out_visited = 1;
	prev->out = node;
	node->in = prev;
}

void	case_backtrack_upstream(t_lem_in *lem_in, t_node **node, t_node *prev)
{
	// prev->out = node;
	(*node)->out_visited = 1;
	(*node)->in_visited = 1;
	prev->out = (*node);
	(*node)->in = prev;

	// go to the originating node
	(*node) = find_a_node(lem_in, (*node)->room->parent);
	(*node)->in_visited = 1;

}

void	case_flow_full(t_node *node, t_node *prev)
{
	node = NULL;
	prev = NULL;
	node = prev;
	prev = node;
	return ;
}

void	follow_node_path(t_lem_in *lem_in, t_node *node)
{
	t_node	*prev;
	t_node	*current;
	//int		flow;

	//flow = 0;	// zero until entered flow for first time;
	current = node;
	while (current->room != lem_in->end_room)
	{
		// if (!node->in)
		// 	node->in = prev;
		prev = current;
		current = return_shortest_node(lem_in, current);
		if (current == NULL)
			return ;
		if (current->room == lem_in->end_room)
		{
			prev->out = current;
			return ;
		}
		if (current->in == NULL && current->in == NULL)
			case_travel_upstream(current, prev);
		else if (current->in_visited == 0 && current->out_visited == 0)
		{
			case_backtrack_upstream(lem_in, &current, prev);
		}
		else
			case_flow_full(current, prev);
		if (current == NULL)
			return ;
		// {
		// 	if (node->in != NULL)
		// 	{
		// 		node->in_visited = 1;
		// 	}
		// 	if (prev->out_visited != NULL)
		// 		prev->out_visited = 1;
		// 	prev->out = node;
		// 	node->in = prev;			
		// }
	}
}


void	find_that_path(t_lem_in *lem_in, t_room *room)
{
	// t_room	*neighbor;
	t_node	*node;
	// t_node	*room_node;
	// int		i;

	// i = 0;
	node = find_a_node(lem_in, room);
	follow_node_path(lem_in, node);
	// prev = room;
	// neighbor = room->neighbors[++i];
	// while (neighbor)
	// {
		
	// 	neighbor = room->neighbors[++i];
	// }

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
	node->out = find_a_node(lem_in, temp->room);
	while (temp)
	{
		node = find_a_node(lem_in, temp->room);
		node->in = prev;
		prev = node;
		temp = temp->next_path;
		if (temp)
			node->out = find_a_node(lem_in, temp->room);
	}
}

t_path	*create_path_node(t_lem_in *lem_in, t_node *node)
{
	t_node	*temp;
	t_path	*path;

	path = lem_in_add_new_path(lem_in->start_room);
	temp = node;
	while (temp->room != lem_in->end_room)
	{
		lem_in_add_to_path(&path, temp->room);
		temp = temp->out;
		if (temp == NULL)
		{
			handle_error(lem_in, "ERROR no path found from nodes.");
			exit(-1);
		}
	}
	lem_in_add_to_path(&path, lem_in->end_room);
	// start_to_end(lem_in, &path);
	return (path);
}

void	start_to_end_node(t_lem_in *lem_in, t_path **path)
{
	t_path	*temp;
	t_path	*new_path;
	// t_path	*start_of_new_path;

	temp = *path;
	new_path = lem_in_add_new_path(lem_in->end_room);
	temp = temp->next_path;
	while (temp->next_path)
	{
		lem_in_add_to_path(&new_path, temp->room);
		temp = temp->next_path;
	}
	lem_in_add_to_path(&new_path, lem_in->start_room);
	free(*path);
	*path = new_path;
	// start_of_new_path = new_path;
	// while (*path)
	// {
	// 	(*path)->room = new_path->room;
	// 	*path = (*path)->next_path;
	// 	new_path = new_path->next_path;
	// }
	// free_a_path(start_of_new_path);
}


void	path_from_node(t_lem_in *lem_in, t_node *node)
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
	path = create_path_node(lem_in, node);
	start_to_end_node(lem_in, &path);
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

void	add_paths_from_node(t_lem_in *lem_in)
{
	t_room	*room;
	int		i;

	i = 0;
	room = lem_in->start_room->neighbors[++i];
	while (room)
	{
		path_from_node(lem_in, find_a_node(lem_in, room));
		room = lem_in->start_room->neighbors[++i];
	}

}

void	edmonkarp(t_lem_in *lem_in)
{
	t_room	*room;
	int		i;

	i = 0;
	set_all_visited_to_zero(lem_in);
	set_nodes_for_path(lem_in, lem_in->paths[0]);
	print_node_paths(lem_in);
	room = lem_in->start_room->neighbors[++i];
	while (room)
	{
		find_that_path(lem_in, room);
		ft_printf("\n new node paths with room: %s\n", room->name);
		print_node_paths(lem_in);
		room = lem_in->start_room->neighbors[++i];
	}

	ft_printf("after change_paths_order\n");
	print_paths(lem_in);
	add_paths_from_node(lem_in);
	i = 0;
	ft_printf("after change_paths_order\n");
	print_paths(lem_in);
	// change_paths_order(lem_in);
	bubble_sort_paths(lem_in);
	remove_duplicates(lem_in, i);
}

