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

// void	path_to_path(t_path *path_1, t_path *path_2)
// {

// }

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

void	free_paths_array_only(t_lem_in *lem_in)
{
	t_path	*paths;
	int		i;

	i = 0;
	if (lem_in->paths == NULL)
		return ;
	paths = lem_in->paths[i];
	while (paths)
	{
		free(paths);
		paths = NULL;
		paths = lem_in->paths[++i];
	}
	free(lem_in->paths);
	lem_in->paths = NULL;
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
	// free_paths_array_only(lem_in);
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
	if (lem_in->end_room->neighbors == NULL || lem_in->start_room->neighbors == NULL)
		handle_error(lem_in, "No path found.");
	room = lem_in->end_room->neighbors[i];
	start_neighbors = ft_lstlen(lem_in->start_room->neighbors);
	fd_sho_path(lem_in, room, lem_in->end_room, lem_in->start_room);
	if (lem_in->paths == NULL)
		handle_error(lem_in, "No path found.");
	room = lem_in->end_room->neighbors[++i];
	while (room != NULL)
	{
		check_path(lem_in, room, lem_in->end_room, lem_in->start_room);
		// fd_sho_path(lem_in, room, lem_in->end_room, lem_in->start_room);
		start_neighbors--;
		room = lem_in->end_room->neighbors[++i];
	}
}
