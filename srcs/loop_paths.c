/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_paths.c                                       :+:      :+:    :+:   */
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
*	@param1	Number of paths
*	@return paths array with shortest path at index [0]
*/
t_path	**create_paths(t_lem_in *lem_in, size_t	size)
{
	t_path	**paths;
	t_path	*path;
	size_t	i;

	i = 1;
	paths = (t_path **)malloc(sizeof(t_path *) * (size + 1));
	path = get_shortest_path(lem_in);
	paths[0] = path;
	while (i <= size)
		paths[i++] = NULL;
	return (paths);
}
