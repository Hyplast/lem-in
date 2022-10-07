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
*	@return Get a different shortest path from lem-in paths.
*	@return 1 if swap succesfull
*	@return 0 if swap not succesfull
*
int	swap_old_path_ver_old(t_lem_in *lem_in, t_path **paths, int j)
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
				return (1);
			}
		}
		i++;
	}
	paths[j] = replace;
	return (0);
}
*/

int	swap_old_path(t_lem_in *lem_in, t_path **paths, int j)
{
	int		i;
	t_path	*replace;
	int		unique;

	i = 0;
	j = (int)count_paths(paths) - j - 1;
	replace = paths[j];
	printf("-replacing path:%dlength;%s;%s-\n", replace->path_length,
		replace->next_path->room->name,
		replace->next_path->next_path->room->name);
	while (lem_in->paths[i])
	{
		if (replace != lem_in->paths[i])
		{
			unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
			if (unique == 1)
			{
				paths[j] = lem_in->paths[i];
				printf(" *-with path:%dlength;%s;%s-\n", paths[j]->path_length,
					paths[j]->next_path->room->name,
					paths[j]->next_path->next_path->room->name);
				return (1);
			}
		}
		i++;
	}
	// paths[j] = replace;
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
	while (unique == 0 && lem_in->paths[++i] != NULL)
	{
		new_path = lem_in->paths[i];
		unique = check_all_paths_uniq(lem_in, new_path, paths);
	}
	if (unique)
	{
		while (paths[j])
			j++;
		paths[j++] = new_path;
		paths[j] = NULL;
		printf("-added path:%dlength;%s;%s-\n", new_path->path_length,
			new_path->next_path->room->name,
			new_path->next_path->next_path->room->name);
		return (1);
	}
	return (0);
}

int	return_n_paths(t_lem_in *lem_in, t_path **paths, int start_neigh)
{
	int	lem_in_path_count;
	int	paths_count;
	int	value;
	int	path_length;

	lem_in_path_count = (int)count_paths(lem_in->paths);
	paths_count = (int)count_paths(paths);
	if (lem_in_path_count == paths_count)
		return (start_neigh);
	if (paths_count > 1)
	{
		path_length = paths[0]->path_length;
		value = paths[1]->path_length;
		if (lem_in->ants_count + path_length - 1 < value)
			value = (int)start_neigh;
		else
			value = paths_count;
	}
	else
		value = paths_count;
	return ((size_t)value);
}

/*
*	If path is unique, replace it to paths.
*
int		check_and_add_old(t_lem_in *lem_in, t_path *path_1, t_path **paths, t_path *replace)
{
	int	unique;
	int	i;

	if (path_1 == replace)
		return (0);
	unique = check_all_paths_uniq(lem_in, path_1, paths);
	if (unique == 1)
	{
		i = (int)count_paths(paths);
		paths[i] = path_1;
		// paths[i] = NULL;
	}
	return (unique);
}
*/

/*
int		find_permuntations_old(t_lem_in *lem_in, t_path **paths, int size)
{
	int		unique;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	paths[j++] = lem_in->paths[i];
	while (j < size)
	{
		unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
		while (unique == 0 && (i < lem_in->paths_count - 1))
			unique = check_all_paths_uniq(lem_in, lem_in->paths[++i], paths);
		if (unique == 1)
			paths[j++] = lem_in->paths[i];
		else
		{
			if (k > lem_in->paths_count)
			{
				j--;
				k = 0;
			}
			if (j < 1)
				return (0);
			paths[--j] = lem_in->paths[k++];
		}
		i = 0;
	}
	return (1);
}
*/

void	add_path_to_paths(t_path **paths, t_path *path)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	paths[i] = path;
}

int		remove_path_from_paths(t_lem_in *lem_in, t_path **paths)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (paths[i] != NULL)
	{
		i++;
	}
	i--;
	while (paths[i] != lem_in->paths[j])
		j++;
	paths[i] = NULL;
	return (j);
}

/*
*	Permutations !number_of_paths.
*	@return !number_of_paths
*/
int		calculate_max_times(int	paths)
{
	int	i;
	int	value;

	value = 0;
	i = 0;
	while(i < paths)
		value = value + paths - i++;
	return (value);
}

int	return_path_len(t_lem_in *lem_in, t_path **paths, int unique)
{
	static int	last_removed;
	static int	times_called;
	static int	max_times_called;
	int			removed;
	int			paths_count;

	if (times_called == 0)
		max_times_called = calculate_max_times(lem_in->paths_count);
	times_called++;
	if (times_called >= max_times_called)
		return(lem_in->paths_count + 1);
	if (unique == 0)
	{
		removed = last_removed;
		last_removed = remove_path_from_paths(lem_in, paths);
		if (last_removed == 0)
			return (1);
		paths_count = (int)count_paths(paths);
		while ((last_removed == removed || last_removed == lem_in->paths_count - 1) 
				&& paths_count != 0)
		{
			paths_count = (int)count_paths(paths);
			if (paths_count > 0)
				last_removed = remove_path_from_paths(lem_in, paths);
		}
		return (last_removed + 1);
	}
	return (0);
}

void	path_copy(t_path **paths, t_path **copy)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
	{
		copy[i] = paths[i];
		i++;
	}
}

/*
*	Sidenote; is the amount of neighbors the start or end room necessary to know?
*	doesn't the algorithm check for unique path so it cannot find more unique paths
*	than the amount of neighbors?
*/
void	calculate_optimal_paths_extend(t_lem_in *lem_in, t_path **paths, t_path **optimun, float min_turns)
{
	float	recent_turns;
	int		i;
	int		unique;

	i = 0;
	while (i < lem_in->paths_count + 1)
	{
		unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
		while (unique == 0 && lem_in->paths[++i] != NULL)
			unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
		if (unique == 1)
		{
			add_path_to_paths(paths, lem_in->paths[i]);
			recent_turns = calculate_path_turns(lem_in, paths);
			if (recent_turns < min_turns)
			{
				min_turns = recent_turns;
				path_copy(paths, optimun);
			}
		}
		i = return_path_len(lem_in, paths, unique);
	}
	path_copy(optimun, paths);
}

/*
*	Calculate the shortest paths with least amount of turns to move the 
*	ant throught. 
*
*
*/
void	calculate_optimal_paths(t_lem_in *lem_in)
{
	t_path	**paths;
	t_path	**optimun;
	float	min_turns;
	int		start_neigbors;

	start_neigbors = calculate_neigbors(lem_in);
	paths = create_paths(lem_in, (size_t)start_neigbors);
	optimun = create_paths(lem_in, (size_t)start_neigbors);
	min_turns = calculate_path_turns(lem_in, paths);
	if (lem_in->paths_count != 1 && start_neigbors != 1)
		calculate_optimal_paths_extend(lem_in, paths, optimun, min_turns);
	lem_in->paths = paths;
	lem_in->paths_count = (int)count_paths(lem_in->paths);
}

/*
*	Calculate shortest paths for ants. Max paths is whichever is lower, amount of 
*	neighbors of start or end rooms. Replace paths in ascending order into lem-in.
*	TODO: add start_neighbors and end_neighbors and update paths_count to lem_in.
*	go through the paths until until until
*/
void	calculate_optimal_paths_old(t_lem_in *lem_in)
{
	int		start_neigbors;
	t_path	**paths;
	int		value;
	int		j;
	int		n_paths;

	j = 0;
	start_neigbors = calculate_neigbors(lem_in);
	paths = create_paths(lem_in, (size_t)start_neigbors);
	n_paths = (int)count_paths(paths);
	if (lem_in->paths_count != 1 && start_neigbors != 1)
	{
		if (lem_in->ants_count > lem_in->paths[1]->path_length - lem_in->paths[0]->path_length)
		{
			while (n_paths < start_neigbors)
			{
				value = add_a_path(lem_in, paths);
				while (value == 0)
				{
					value = swap_old_path(lem_in, paths, j++);
					if (value == 1)
						value = add_a_path(lem_in, paths);
				}
				j = 0;
				n_paths = return_n_paths(lem_in, paths, start_neigbors);//count_paths(paths);
			}
		}
	}
	check_for_max_neigbor_option(lem_in, paths, start_neigbors);
}
