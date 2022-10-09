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
*	Permutations !number_of_paths.
*	@return !number_of_paths
*/
int	calculate_max_times(int paths)
{
	int	i;
	int	value;

	value = 0;
	i = 0;
	while (i < paths)
		value = value + paths - i++;
	return (value);
}

int	return_path_len(t_lem_in *lem_in, t_path **paths, int unique, int removed)
{
	static int	last_removed;
	static int	times_called;
	static int	max_times_called;
	int			paths_count;

	if (times_called == 0)
		max_times_called = calculate_max_times(lem_in->paths_count);
	if (++times_called >= max_times_called)
		return (lem_in->paths_count + 1);
	if (unique == 0)
	{
		removed = last_removed;
		last_removed = remove_path_from_paths(lem_in, paths);
		if (last_removed == 0)
			return (1);
		paths_count = (int)count_paths(paths);
		while ((last_removed == removed || last_removed
				== lem_in->paths_count - 1) && paths_count != 0)
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
void	calculate_optimal_paths_extend(t_lem_in *lem_in, t_path **paths,
			t_path **optimun, float min_turns)
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
		i = return_path_len(lem_in, paths, unique, i);
	}
	path_copy(optimun, paths);
}

void	free_non_used_paths(t_lem_in *lem_in, t_path **new_paths)
{
	int		i;
	int		j;
	int		n_paths;

	j = 0;
	i = 0;
	n_paths = (int)count_paths(new_paths);
	while (lem_in->paths[i] != NULL)
	{
		while (j < n_paths && new_paths[j] != lem_in->paths[i])
			j++;
		if (n_paths == j)
		{
			free_a_path(lem_in->paths[i]);
			// free(lem_in->paths[i]);
			// lem_in->paths[i] = NULL;
		}
		j = 0;
		i++;
	}
	free(lem_in->paths);
	lem_in->paths = NULL;
}

/*
*	Calculate the shortest paths with least amount of turns to move the 
*	ant throught. 
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
	free_non_used_paths(lem_in, paths);
	// free(lem_in->paths);
	lem_in->paths = paths;
	lem_in->paths_count = (int)count_paths(lem_in->paths);
}
