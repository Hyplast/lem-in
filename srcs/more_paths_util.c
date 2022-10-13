/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_paths_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


// t_room	*not_neighbors(t_room,)

/*  
*	set each room that has a path running throught it
*   to visited.
*/
void	set_occupied_path_rooms(t_lem_in *lem_in)
{
    t_path	*path;
	t_path	*temp;
	int		i;

	i = 0;
	path = lem_in->paths[i];
	while (path)
	{
		temp = path;
		while (temp)
		{
			temp->room->visited = 1;
			temp = temp->next_path;
		}
		path = lem_in->paths[++i];
	}
}

void	set_start_end_neighbors(t_lem_in *lem_in, int start, int end)
{
	t_room	*temp;
	int		i;

	i = 0;
	temp = lem_in->start_room->neighbors[i];
	while (temp)
	{
		temp->visited = start;
		temp = lem_in->start_room->neighbors[++i];
	}
	i = 0;
	temp = lem_in->end_room->neighbors[i];
	while (temp)
	{
		temp->visited = end;
		temp = lem_in->end_room->neighbors[++i];
	}
	lem_in->end_room->visited = 0;
	lem_in->start_room->visited = 0; 
}
