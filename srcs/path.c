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

void	lem_in_add_to_path(t_path **path, t_room *room)
{
	t_path	*new_path;

	new_path = (t_path *)malloc(sizeof(t_path));
	new_path->room = room;
	new_path->path_length = (*path)->path_length + 1;
	new_path->next_path = *path;
	*path = new_path;
}

t_path	*lem_in_add_new_path(t_room *room)
{
	t_path	*path;

	path = (t_path *)malloc(sizeof(t_path));
	path->next_path = NULL;
	path->path_length = 0;
	path->room = room;
	return (path);
}

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
			handle_error(lem_in, "No path found.");
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
*	Find paths from end to start using neihgboring distance.
*	Only add path if it's distance is less than (distance + ants - 1). 
*	@return NULL if no path is found.
*/
void	find_paths(t_lem_in *lem_in)
{
	// int		threshold;
	int		i;
	size_t	start_neighbors;
	t_room	*room;

	i = 0;
	room = lem_in->end_room->neighbors[i];
	// threshold = lem_in->ants_count + lem_in->end_room->distance - 1;
	start_neighbors = ft_lstlen(lem_in->start_room->neighbors);
	fd_sho_path(lem_in, room, lem_in->end_room, lem_in->start_room);
	if (lem_in->paths == NULL)
	{
		handle_error(lem_in, "No path found.");
		exit(-1);
	}
	room = lem_in->end_room->neighbors[++i];
	while (room != NULL)// && start_neighbors > 1 && room->distance < threshold)
	{
		fd_sho_path(lem_in, room, lem_in->end_room, lem_in->start_room);
		start_neighbors--;
		room = lem_in->end_room->neighbors[++i];
	}
}
