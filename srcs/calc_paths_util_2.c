/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_paths_util_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/08/29 00:54:39 by severi           ###   ########.fr       */
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

void	add_path_to_paths(t_path **paths, t_path *path)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	paths[i] = path;
}

/*
*	Use bubble sorting to sort the paths in length ascending order.
*/
void	bubble_sort_paths(t_lem_in *lem_in)
{
	t_path	**paths;
	t_path	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	paths = lem_in->paths;
	while (lem_in->paths[i])
	{
		while (paths[j])
		{
			if (lem_in->paths[i]->path_length < paths[j]->path_length)
			{
				temp = paths[j];
				paths[j] = lem_in->paths[i];
				lem_in->paths[i] = temp;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

/*
*	Return whichever has lower amount of neighbors, start or end room.
*/
int	calculate_neigbors(t_lem_in *lem_in)
{
	int		start_neigbors;
	int		end_neigbors;

	start_neigbors = (int)ft_lstlen(lem_in->start_room->neighbors);
	end_neigbors = (int)ft_lstlen(lem_in->end_room->neighbors);
	if (start_neigbors > end_neigbors)
		start_neigbors = end_neigbors;
	return (start_neigbors);
}
