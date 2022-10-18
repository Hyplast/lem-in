/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	Find the shortest path between start and end rooms different than last path.
*	@return	the shortest path between start and end rooms.
*	@return NULL if no path is found.
*/
t_path	*create_path(t_lem_in *lem_in, t_room *room, t_room *start, t_room *end)
{
	t_path	*path;

	path = lem_in_add_new_path(end);
	while (room != end)
	{
		lem_in_add_to_path(&path, room);
		room = return_shortest_room(start, room);
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
void	fd_sho_path(t_lem_in *lem_in, t_room *room, t_room *start, t_room *end)
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
	path = create_path(lem_in, room, start, end);
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
void	check_path(t_lem_in *lem_in, t_room *room, t_room *start, t_room *end)
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
		temp = return_shortest_room(start, temp);
		if (temp == prev || temp == after || temp == NULL)
			return ;
		prev = temp;
		if (i++ % 2 == 0)
			after = temp;
	}
	fd_sho_path(lem_in, room, start, end);
}

void	find_valid_path(t_lem_in *lem_in)
{
	int		i;
	t_room	*room;

	i = 0;
	room = lem_in->end_room->neighbors[i];
	while (lem_in->paths == NULL)
	{
		check_path(lem_in, room, lem_in->end_room, lem_in->start_room);
		room = lem_in->end_room->neighbors[++i];
		if (room == NULL)
			return ;
	}
}

/*
*	Find paths from end to start using neihgboring distance.
*	
*	@return NULL if no path is found.
*/
void	find_paths(t_lem_in *lem_in)
{
	int		i;
	size_t	start_neighbors;
	t_room	*room;

	i = 0;
	if (lem_in->end_room->neighbors == NULL
		|| lem_in->start_room->neighbors == NULL)
		handle_error(lem_in, "ERROR no path found.");
	find_valid_path(lem_in);
	room = lem_in->end_room->neighbors[i];
	start_neighbors = ft_lstlen(lem_in->start_room->neighbors);
	check_path(lem_in, room, lem_in->end_room, lem_in->start_room);
	if (lem_in->paths == NULL)
		handle_error(lem_in, "ERROR no path found.");
	room = lem_in->end_room->neighbors[++i];
	while (room != NULL)
	{
		check_path(lem_in, room, lem_in->end_room, lem_in->start_room);
		start_neighbors--;
		room = lem_in->end_room->neighbors[++i];
	}
}

void	swap_start_end(t_lem_in *lem_in)
{
	t_path	*path;
	int		i;

	i = 0;
	while (lem_in->paths[i])
	{
		path = lem_in->paths[i];
		if (path->room == lem_in->end_room)
		{
			path->room = lem_in->start_room;
			path = path->next_path;
			while (path)
			{
				if (path->room == lem_in->start_room)
					path->room = lem_in->end_room;
				path = path->next_path;
			}
		}
		i++;
	}
}

void	recalculate_bfs(t_lem_in *lem_in)
{
	t_queue	*queue;
	t_room	*room;
	int		i;

	i = 0;
	room = lem_in->end_room->neighbors[++i];
	while (room)
	{
		queue = init_queue();
		set_one_path_to_visited(lem_in, lem_in->paths[i - 1]);

		bread_first_search(lem_in, &queue, lem_in->start_room);
		find_the_shortest_path(lem_in, i);
		room = lem_in->end_room->neighbors[++i];
		swap_start_end(lem_in);
		print_rooms(lem_in);
		print_paths(lem_in);
	
	}
}

void	find_the_shortest_path(t_lem_in *lem_in, int i)
{
	t_room	*room;
	find_valid_path(lem_in);

	room = lem_in->end_room->neighbors[i];
	check_path(lem_in, room, lem_in->end_room, lem_in->start_room);
	if (lem_in->paths == NULL)
		handle_error(lem_in, "ERROR no path found.");
}