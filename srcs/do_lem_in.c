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

size_t		ft_lstlen(t_room **neighbors)
{
	size_t		len;

	len = 0;
    if (neighbors == NULL)
		return (len);
	while (neighbors[len] != NULL)
		len++;
	return (len);
}


void	print_neighbors(t_room *room)
{
	//t_room	*temp;
	size_t	i;

	i = 0;
	ft_printf("room \"%s\" has %i neighbors and they are: ", room->name, ft_lstlen(room->neighbors));
	if (room->neighbors == NULL)
	{
		ft_printf("\n");
		return ;
	}
	//temp = room->neighbors[0];
	while (room->neighbors[i] != NULL)
	{
		ft_printf("\"%s\" with %i distance, ", room->neighbors[i]->name, room->neighbors[i]->distance);
		i++;
		//temp = room->neighbors[i];
	}
	ft_printf("\n");
}

/*
*	Add neighbors to the rooms. From shortest distance to longest.
*/
void    add_neighbors(t_room *room_1, t_room *room_2)
{
    t_room  **neighbors;
    int i;
    size_t len;

    i = 0;
    len = ft_lstlen(room_1->neighbors);
    neighbors = (t_room **)malloc(sizeof(t_room *) * (len + 1 + 1 ));
    if (len == 0)
	{
        neighbors[0] = room_2;
		neighbors[1] = NULL;
	}
	else
    {
        while (i < (int)len)
        {
            neighbors[i] = room_1->neighbors[i];
            i++;
        }
		neighbors[len] = room_2;
		neighbors[len + 1] = NULL;
    }
    room_1->neighbors = neighbors;
}


/*
*	Check if the addresses point to the same memory location
*/
void	go_to_linked_rooms(t_lem_in *lem_in, t_queue **queue)
{
	t_link	*temp;
	static int	distance;
	int			just_once;

	just_once = 0;
	temp = lem_in->links;
	while (temp != NULL)
	{
		// ft_printf("temp->room_1 : %p : %s<-> (*queue)->room : %p : %s\n", temp->room_1, temp->room_1->name, (*queue)->room, (*queue)->room->name);
		// ft_printf("sizeof(temp->room_1: %lu\n", sizeof(temp->room_1));
		// ft_printf(sizeof(temp->room_1));
		// ft_printf("\n");
		if ((ft_memcmp(temp->room_1, (*queue)->room, sizeof(temp->room_1)) == 0))
		{
			if (temp->room_2->visited == 0)
			{
				if (just_once == 0)
				{
					distance++;
					just_once = 1;
				}
				temp->room_2->visited = 1;
				temp->room_2->distance = distance;
				// ft_printf("%s\n", temp->room_2->name);
				//add_neighbors(temp->room_1, temp->room_2);
				insert(queue, temp->room_2);
			}
		}
		temp = temp->next;
	}
}

/*
*	Bread first traversal to find path lenghts between start and end rooms.
*	Stop if more paths are found than ants exist.
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
		ft_printf("\nStack: %s", (*queue)->room->name);
		queue_remove(queue);
	}
	// while (!lem_in->rooms++)
	// {
	// 	lem_in->rooms->visited = 0;
	// }
	ft_printf("\nKKK lem_in->rooms->name : ");
	ft_printf(lem_in->rooms->name);
	ft_printf("\n");
}

// /*
// *	Given room x, find the room y that is the shortest distance to x.
// *	@return	the room that is the shortest distance to x.
// *	@return NULL if no room is found.
// */
// t_room	*return_shortest_room(t_lem_in *lem_in, t_room *room_x)
// {
// 	t_room	*shortest_room;
// 	t_link	*temp_link;
// 	int		shortest_distance;

// 	temp_link = lem_in->links;
// 	shortest_distance = INT32_MAX;
// 	shortest_room = NULL;
// 	while (temp_link != NULL)
// 	{
// 		if (ft_memcmp(temp_link->room_1, room_x, sizeof(room_x)) == 0)
// 		{
// 			if (temp_link->room_2->distance < shortest_distance)
// 			{
// 				shortest_distance = temp_link->room_2->distance;
// 				shortest_room = temp_link->room_2;
// 			}
// 		}
// 		temp_link = temp_link->next;
// 	}
// 	return (shortest_room);
// }

t_room *return_shortest_room(t_room *room)
{
	t_room	*temp;
	t_room	*shortest_room;
	int		shortest_distance;
	int		i;

	i = 0;
	temp = room->neighbors[i];
	shortest_distance = 2147483647;
	while (temp != NULL)
	{
		if (temp->distance < shortest_distance)
		{
			shortest_distance = temp->distance;
			shortest_room = temp;
		}
		temp = room->neighbors[++i];
	}
	return (shortest_room);	
}

/*
*	Find the shortest path between start and end rooms different than last path.
*	@return	the shortest path between start and end rooms.
*	@return NULL if no path is found.
*//*
void	find_unique_path(t_lem_in *lem_in, t_path *path)
{
	t_room	*shortest_room;
	t_path	*temp_path;
	int		shortest_distance;

	temp_path = path;
	shortest_distance = INT32_MAX;
	shortest_room = NULL;
	while (temp_path != NULL)
	{
		if (temp_path->room->distance < shortest_distance)
		{
			shortest_distance = temp_path->room->distance;
			shortest_room = temp_path->room;
		}
		temp_path = temp_path->next;
	}
	if (shortest_room != NULL)
	{
		temp_path = path;
		while (temp_path != NULL)
		{
			if (ft_memcmp(temp_path->room, shortest_room, sizeof(shortest_room)) == 0)
			{
				temp_path->room->visited = 1;
				break;
			}
			temp_path = temp_path->next;
		}
	}
}
*/

t_path	*create_a_path(t_lem_in *lem_in, t_room *room)
{
	t_path	*path;

	path = lem_in_add_new_path(lem_in->end_room);

	while (ft_memcmp(room, lem_in->start_room, sizeof(room)) != 0)
	{
		lem_in_add_to_path(&path, room);
		room = return_shortest_room(room);
		if (room == NULL)
		{
			handle_error(lem_in, "No path found.");
			exit(-1);
		}
	}
	lem_in_add_to_path(&path, lem_in->start_room);
	return (path);
}


/*
*	Find the shortest path between start and given room.
*	Add it to the path list.
*	@return void
*/
/*void	find_shortest_path(t_lem_in *lem_in, t_room *room)
{
	t_path	**paths;
	t_path	*path;

    paths = (t_path **)malloc(sizeof(t_path *) * (1 + 1));
	path = create_a_path(lem_in, room);
    paths[0] = path;
	paths[1] = NULL;
	lem_in->paths = paths;
}*/
void	find_n_shortest_path(t_lem_in *lem_in, t_room *room)
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
	path = create_a_path(lem_in, room);
	while (i < len)
	{
		paths[i] = lem_in->paths[i];
		i++;
	}
    paths[len] = path;
	paths[len + 1] = NULL;
	lem_in->paths = paths;
}


/*
	path = create_a_path

        while (i < (int)len)
        {
            paths[i] = room_1->neighbors[i];
            i++;
        }
		paths[len] = room_2;
		paths[len + 1] = NULL;
    room_1->paths = neighbors;

	*/

/*
*	Find paths from end to start using neihgboring distance.
*	Only add path if it's distance is less than (distance + ants - 1). 
*	@return NULL if no path is found.
*/
void	find_paths(t_lem_in *lem_in)
{
	int	threshold;
	size_t	start_neighbors;
	int	i;

	t_room	*room;

	i = 0;
	room = lem_in->end_room->neighbors[i];
	threshold = lem_in->ants_count + lem_in->end_room->distance - 1;
	start_neighbors = ft_lstlen(lem_in->start_room->neighbors);
	//end_neighbors = ft_lstlen(lem_in->end_room->neighbors);
	find_n_shortest_path(lem_in, room);
	if (lem_in->paths == NULL)
	{
		handle_error(lem_in, "No path found.");
		exit(-1);
	}
	room = lem_in->end_room->neighbors[++i];
	print_paths(lem_in);
	while(room != NULL && start_neighbors > 1 && room->distance < threshold)
	{
		find_n_shortest_path(lem_in, room);
		start_neighbors--;
		room = lem_in->end_room->neighbors[++i];
	}
	// {
	// 	while (threshold > room->distance)
	// 	{
	// 		lem_in_add_new_path(lem_in, room);
	// 		find_shortest_path(lem_in, room);
	// 		room = lem_in->end_room->neighbors[i];
	// 	}
	// }
	//fix_unique_paths(lem_in);
}


/*
*	Find neighbors of the rooms. From shortest distance to longest.
*/
void	find_neighbors(t_lem_in *lem_in)
{
	t_link	*temp;

	temp = lem_in->links;
	while (temp != NULL)
	{
		add_neighbors(temp->room_1, temp->room_2);
		temp = temp->next;
	}
}

/*
*	Set visited rooms to zero in order to keep count which rooms are occupied by ants.
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
		while(temp)
		{
			temp->room->visited = 0;
			temp = temp->next_path;
		}
		path = lem_in->paths[++i];
	}
}

void	do_lem_in(t_lem_in *lem_in)
{
	t_queue	*queue;

	queue = init_queue();
	// print_rooms(lem_in);
	// print_links(lem_in);
	// print_ants(lem_in);
	// ft_printf("room_name : %s\n", lem_in->rooms->name);
	// ft_printf("ants : %i\n", lem_in->ants->ant_id);
	// ft_printf("nextl line\n");
	bread_first_search(lem_in, &queue);
	find_neighbors(lem_in);
	// ft_printf("\n $£€\n");
	// ft_printf(lem_in->rooms->name);
	// ft_printf("\n");
	// print_rooms(lem_in);
	// ft_printf("START ROOM as t_room->name: %s \n", lem_in->start_room->name);
	// ft_printf("END ROOM as t_room->name: %s \n", lem_in->end_room->name);
	// print_neighbors(lem_in->rooms);
	// print_neighbors(lem_in->rooms->next);
	// print_neighbors(lem_in->rooms->next->next);
	// print_neighbors(lem_in->rooms->next->next->next);
	// print_neighbors(lem_in->rooms->next->next->next->next);
	find_paths(lem_in);
	// ft_printf(queue->room->name);
	print_paths(lem_in);
	set_visited_to_zero(lem_in);
	move_ants(lem_in);
	// print_moves(lem_in);
	ft_printf("\n");
}
