/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_reversed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	Find the shortest path between end and start rooms different than last path.
*	@return	the shortest path between start and end rooms.
*	@return NULL if no path is found.
*//*
t_path	*create_a_path(t_lem_in *lem_in, t_room *room, t_room *start, t_room *end)
{
	t_path	*path;

	path = lem_in_add_new_path(end);
	while (room != end)
	{
		lem_in_add_to_path(&path, room);
		room = return_shortest_room(room);
		if (room == NULL)
		{
			handle_error(lem_in, "No path found.");
			exit(-1);
		}
	}
	lem_in_add_to_path(&path, start);
	return (path);
}
*/
/*
*	Find the shortest path between start and given room.
*	Add it to the path list.
*	@return void
*//*
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
	free(lem_in->paths);
	lem_in->paths = paths;
}
*/

void	change_paths_order(t_lem_in *lem_in)
{
	t_path	*path;
	int		i;

	i = 0;
	path = lem_in->paths[i];
	while (path)
	{
		path = lem_in->paths[++i];
	}
}

/*
*	Find paths from end to start using neihgboring distance.
*	Only add path if it's distance is less than (distance + ants - 1). 
*	@return NULL if no path is found.
*/
void	find_paths_reverse_order(t_lem_in *lem_in)
{
	// int		threshold;
	int		i;
	size_t	start_neighbors;
	t_room	*room;
	// t_path	**paths;

	i = 0;
	room = lem_in->start_room->neighbors[i];
	// threshold = lem_in->ants_count + lem_in->start_room->distance - 1;
	start_neighbors = ft_lstlen(lem_in->start_room->neighbors);
	find_n_shortest_path(lem_in, room, lem_in->start_room, lem_in->end_room);
	room = lem_in->start_room->neighbors[++i];
	while ((size_t)i < start_neighbors)
	{
		find_n_shortest_path(lem_in, room, lem_in->start_room, lem_in->end_room);
		room = lem_in->start_room->neighbors[++i];
	}
	// while (room != NULL && start_neighbors > 1 && room->distance < threshold)
	// {
	// 	find_n_shortest_path(lem_in, room);
	// 	start_neighbors--;
	// 	room = lem_in->end_room->neighbors[++i];
	// }
}
