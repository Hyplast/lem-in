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
*	Count the amount of paths
*	@param	t_paths **paths
*	@return	amount of paths
*/
size_t	count_paths(t_path **paths)
{
	size_t		len;

	len = 0;
	if (paths == NULL)
		return (len);
	while (paths[len] != NULL)
		len++;
	return (len);
}

void	end_to_start(t_lem_in *lem_in, t_path *path)
{
	while (path)
	{
		if (path->room == lem_in->end_room)
			path->room = lem_in->start_room;
		else if (path->room == lem_in->start_room)
			path->room = lem_in->end_room;
		path = path->next_path;
	}
}

void	start_to_end(t_lem_in *lem_in, t_path **path)
{
	t_path	*temp;
	t_path	*new_path;
	t_path	*start_of_new_path;

	temp = *path;
	new_path = lem_in_add_new_path(lem_in->end_room);
	temp = temp->next_path;
	while (temp->next_path)
	{
		lem_in_add_to_path(&new_path, temp->room);
		temp = temp->next_path;
	}
	lem_in_add_to_path(&new_path, lem_in->start_room);
	start_of_new_path = new_path;
	while (*path)
	{
		(*path)->room = new_path->room;
		*path = (*path)->next_path;
		new_path = new_path->next_path;
	}
	free_a_path(start_of_new_path);
}

/*
*	Fix starting path to lem_in->start and ending path to lem_in->end.
*/
void	change_paths_order(t_lem_in *lem_in)
{
	t_path	*path;
	int		i;

	i = 0;
	path = lem_in->paths[i];
	while (path)
	{
		if (path->room == lem_in->start_room)
			start_to_end(lem_in, &path);
		else if (path->room == lem_in->end_room)
			end_to_start(lem_in, path);
		path = lem_in->paths[++i];
	}
}

/*
*	Find paths from start to end using neighboring distance.
*	
*	@return NULL if no path is found.
*/
void	find_paths_reverse_order(t_lem_in *lem_in)
{
	int		i;
	size_t	start_neighbors;
	t_room	*room;

	i = 0;
	start_neighbors = ft_lstlen(lem_in->start_room->neighbors);
	while ((size_t)i < start_neighbors)
	{
		room = lem_in->start_room->neighbors[i++];
		check_path(lem_in, room,
			lem_in->start_room, lem_in->end_room);
	}
}
