/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	Given room x, find the room y that is the shortest distance to x.
*	@return	the room that is the shortest distance to x.
*	@return NULL if no room is found.
*/
t_room	*return_shortest_non_occupied_room(t_room *start, t_room *room)
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
			if (temp != start && temp->visited == 0)
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
t_path	*create_path_non_occupied(t_lem_in *lem_in, t_room *room, t_room *start, t_room *end)
{
	t_path	*path;

	path = lem_in_add_new_path(start);
	while (room != end)
	{
		lem_in_add_to_path(&path, room);
		room = return_shortest_non_occupied_room(start, room);
		if (room == NULL)
		{
			handle_error(lem_in, "No path found.\n");
			exit(-1);
		}
	}
	lem_in_add_to_path(&path, end);
	return (path);
}

/*
*	Find the shortest path between start and given room.
*	Add it to the path list.
*	@return void
*/
void	fd_sho_path_non_occupied(t_lem_in *lem_in, t_room *room, t_room *start, t_room *end)
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
	path = create_path_non_occupied(lem_in, room, start, end);
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
*	Check that a valid path can be found between these rooms.
*/
void	check_path_non_occupied(t_lem_in *lem_in, t_room *room, t_room *start, t_room *end)
{
	t_room	*prev;
	t_room	*temp;
	t_room	*after;
	int		i;

	i = 0;
	temp = room;
	while (temp != end)
	{
		if (temp->distance == 0)
			return ;
		temp = return_shortest_non_occupied_room(start, temp);
		if (temp == prev || temp == after || temp == NULL)
			return ;
		prev = temp;
		if (i++ % 2 == 0)
			after = temp;
	}
	fd_sho_path_non_occupied(lem_in, room, start, end);
}

/*
*	Fix starting path from end to start and start to end;
*/
void	change_paths_order_reverse(t_lem_in *lem_in)
{
	t_path	*path;
	int		i;

	i = 0;
	path = lem_in->paths[i];
	while (path)
	{
		if (path->room == lem_in->end_room)
			start_to_end(lem_in, &path);
		path = lem_in->paths[++i];
	}
	i = 0;
	bubble_sort_paths(lem_in);
	remove_duplicates(lem_in, i);
}

/*
*   Inorder to take into account path superpositions, try to find paths
*   different from previous paths by looking for paths running throught
*   different rooms. First set each room that has a path running throught it
*   to visited except start and end neighbors.
*/
void	more_paths(t_lem_in *lem_in)
{
	int		i;
	t_room	*room;
	t_queue	*queue;

	queue = init_queue();
	i = 0;
	set_all_visited_to_zero(lem_in);
	set_occupied_path_rooms(lem_in);
	set_start_end_neighbors(lem_in, 0, 0);
	bread_first_search(lem_in, &queue, lem_in->end_room);
	set_all_visited_to_zero(lem_in);
	set_start_end_neighbors(lem_in, 1, 0);
	lem_in->start_room->distance = 2147483647;
	room = lem_in->start_room->neighbors[i];
	while (room)
	{
		check_path_non_occupied(lem_in, room, lem_in->start_room, lem_in->end_room);
		room = lem_in->start_room->neighbors[++i];
	}
	print_paths(lem_in);
	change_paths_order_reverse(lem_in);
	lem_in->paths_count = (int)count_paths(lem_in->paths);
}

