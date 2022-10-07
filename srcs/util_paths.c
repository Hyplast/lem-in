/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
*	@return Shortest path from lem-in paths.
*/
t_path	*get_shortest_path(t_lem_in *lem_in)
{
	t_path	*path;
	t_path	*temp;
	int		i;

	i = 0;
	temp = lem_in->paths[i];
	path = temp;
	while (temp)
	{
		if (path->path_length > temp->path_length)
			path = temp;
		temp = lem_in->paths[++i];
	}
	return (path);
}

/*
*	Check whether paths have matching rooms excluding start and end rooms.
*	@param1 path 1
*	@param2 path 2
*	@return 1 no match, 0 if matching rooms
*/
int	is_path_unique(t_lem_in *lem_in, t_path *path_1, t_path *path_2)
{
	t_path	*temp_1;
	t_path	*temp_2;

	temp_1 = path_1->next_path;
	temp_2 = path_2->next_path;
	while (temp_1->room != lem_in->end_room)
	{
		while (temp_2->room != lem_in->end_room)
		{
			if (temp_1->room == temp_2->room)
				return (0);
			temp_2 = temp_2->next_path;
		}
		temp_2 = path_2->next_path;
		temp_1 = temp_1->next_path;
	}
	return (1);
}

/*
*	Check whether path and paths have matching rooms excluding start and end rooms.
*	Don't compare path to itself.
*	@param1 path 1
*	@param2 paths
*	@return 1 no match, 0 if matching rooms
*/
int	check_all_paths_uniq(t_lem_in *lem_in, t_path *path_1, t_path **paths)
{
	int	i;
	int	result;

	i = 0;
	while (paths[i])
	{
		if (path_1 == paths[i])
			result = 0;
		else
			result = is_path_unique(lem_in, path_1, paths[i]);
		if (result == 0)
			return (0);
		i++;
	}
	return (1);
}
