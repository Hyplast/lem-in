/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/08/29 00:54:39 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	Check whether paths have matching rooms excluding start and end rooms.
*	@param1 path 1
*	@param2 path 2
*	@return 1 no match, 0 if matching rooms
*/
int		is_path_unique(t_lem_in *lem_in, t_path *path_1, t_path *path_2)
{
	t_path	*temp_1;
	t_path	*temp_2;

	temp_1 = path_1->next_path;
	temp_2 = path_2->next_path;
	while(temp_1->room != lem_in->end_room)
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
	while(paths[i])
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

/*
*	@return Get a different shortest path from lem-in paths.
*	@return 1 if swap succesfull
*	@return 0 if swap not succesfull
*/
int	swap_old_path(t_lem_in *lem_in, t_path **paths, int j)
{

	int		i;
	t_path	*replace;
	int		unique;
	i = 0;

	replace = paths[j];
	paths[j] = NULL;
	while (lem_in->paths[i])
	{
		if (replace != lem_in->paths[i])
		{
			unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
			if (unique == 1)
			{
				paths[j] = lem_in->paths[i];
				return 1;
			}
		}
		i++;
	}
	paths[j] = replace;
	return (0);
}

/*
*	Add a new path to new paths array and make sure that it doesn't
*	have overlapping rooms with previous paths. If it has, go to next path until
* 	new path is found. TODO: Check what combinations of path length lead to lowest
*	@return 1 if new path is found and added
*	@return 0 if no path is added
*/
int	add_a_path(t_lem_in *lem_in, t_path **paths)
{
	t_path	*new_path;
	int		i;
	int		j;
	int		unique;

	i = 0;
	j = 0;
	new_path = lem_in->paths[i];
	unique = check_all_paths_uniq(lem_in, new_path, paths);
	while(unique == 0 && lem_in->paths[++i] != NULL)
	{
		new_path = lem_in->paths[i];
		unique = check_all_paths_uniq(lem_in, new_path, paths);
	}
	if (unique)
	{
		while(paths[j])
			j++;
		paths[j++] = new_path;
		paths[j] = NULL;
		return 1;
	}
	return 0;
}

/*
*	Calculate shortest paths for ants. Max paths is whichever is lower, amount of 
*	neighbors of start or end rooms. Replace paths in ascending order into lem-in.
*/
void 	calculate_optimal_paths(t_lem_in *lem_in)
{
	size_t	start_neigbors;
	size_t	end_neigbors;
	t_path	**paths;
	t_path	*path;
	int		value;
	int		j;

	j = 0;
	start_neigbors = ft_lstlen(lem_in->start_room->neighbors);
	end_neigbors = ft_lstlen(lem_in->end_room->neighbors);
	if (start_neigbors > end_neigbors)
		start_neigbors = end_neigbors;
	paths = (t_path **)malloc(sizeof(t_path *) * (start_neigbors + 1));
	path = get_shortest_path(lem_in);
	paths[0] = path;
	paths[1] = NULL;
	while (count_paths(paths) < start_neigbors)
	{
		value = add_a_path(lem_in, paths);
		while(value == 0)
		{
			value = swap_old_path(lem_in, paths, j++);
			if (value == 1)
				value = add_a_path(lem_in, paths);
		}
	}
	lem_in->paths = paths;

}