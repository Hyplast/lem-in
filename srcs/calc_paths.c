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
*	Count the length of the path.
*	@param	t_paths *path
*	@return	length of the path.
*//*
size_t	path_len(t_path *path)
{
	size_t		len;

	len = 0;
	if (paths == NULL)
		return (len);
	while (paths[len] != NULL)
		len++;
	return (len);
}
*/
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
			result = 1;
		else
			result = is_path_unique(lem_in, path_1, paths[i]);
		if (result == 0)
			return (0);
		i++;
	}
	return (1);
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
*	@return Get a different shortest path from lem-in paths.
*/
void	swap_old_path(t_lem_in *lem_in, t_path **paths)
{

	int		i;
	int		j;
	// t_path	*replace;
	int		unique;

	i = 0;
	j = 0;
	// replace = paths[j];
	
	while (lem_in->paths[i])
	{
		unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
		if (unique == 1)
		{
			paths[j] = lem_in->paths[i];
			return ;
		}
		i++;
	}

	// t_path	*path;
	// int		found;
	// int		j;
	// int		i;

	// i = 0;
	// found = -1;
	// j = 0;
	// temp = lem_in->paths[];
	// path = paths[j];

	// while (paths[j])
	// {
	// 	if (temp == paths[j])
	// 		found = j;
	// 	j++;
	// }

	// 	while (lem_in->paths[i] != paths[j])
	// 	{
	// 		j++;
	// 	}
	// }

	// return (path);
}


//	3	->	2
//	2	->	3
//	4	->	4
/*
*	Add a new path to new paths array and make sure that it doesn't
*	have overlapping rooms with previous paths. If it has, go to next path until
* 	new path is found. TODO: Check what combinations of path length lead to lowest
*/
void	add_a_path(t_lem_in *lem_in, t_path **paths)
{
	// int		path_length;
	// size_t	paths_count;
	t_path	*new_path;
	int		i;
	int		j;
	int		unique;

	i = 0;
	j = 0;
	// path_length = path_len(paths);
	// paths_count = count_paths(paths);
	// path_length = paths[0]->path_length;
	//get_shortest_path(lem_in);
	// new_path = lem_in->paths[0];
	while(lem_in->paths[i])
	{
		new_path = lem_in->paths[0];
		unique = check_all_paths_uniq(lem_in, new_path, paths);
		if (unique)
		{
			while(paths[j])
				j++;
			paths[j++] = new_path;
			paths[j] = NULL;
			return ;
		}
		// while(new_path != paths[paths_count])
		// {
		// 	new_path = get_a_new_path(lem_in, paths);
		// 	unique = check_all_paths_uniq(lem_in, new_path, paths);
		// 	if (unique == 1)
		// 	{
		// 		//add_to_paths(lem_in, paths);
		// 	}
			
		// }
		i++;
	}
	swap_old_path(lem_in, paths);
}

/*
*	Use bubble sorting to sort the paths in length ascending order.
*/
void 	bubble_sort_paths(t_lem_in *lem_in)
{
	t_path	**paths;
	t_path	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	paths = lem_in->paths;
	while(lem_in->paths[i])
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
*	Calculate shortest paths for ants. Max paths is whichever is lower, amount of 
*	neighbors of start or end rooms. Replace paths in ascending order into lem-in.
*/
void 	calculate_optimal_paths(t_lem_in *lem_in)
{
	size_t	start_neigbors;
	size_t	end_neigbors;
	t_path	**paths;
	t_path	*path;
	// t_path	*temp;

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
		add_a_path(lem_in, paths);

	}
	lem_in->paths = paths;

}