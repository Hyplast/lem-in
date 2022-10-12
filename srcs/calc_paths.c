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

int	keep_track_times_called(t_lem_in *lem_in)
{
	static int	times_called;
	static int	max_times_called;

	if (times_called == 0)
		max_times_called = calculate_max_times(lem_in->paths_count);
	if (++times_called >= max_times_called - 1)
		return (lem_in->paths_count + 1);
	return (0);
}

int	return_path_len(t_lem_in *lem_in, t_path **paths, int unique, int removed)
{
	static int	last_removed;
	int			paths_count;
	int			i;

	i = keep_track_times_called(lem_in);
	if (i != 0)
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

/*
*	Helper function for calculate optimal paths.
*	Keep the best shortest turn combination stored in optimun
*/
void	calculate_optimal_paths_extend(t_lem_in *lem_in, t_path **paths,
			t_path **optimun, int min_turns)
{
	int	recent_turns;
	int	i;
	int	unique;

	i = 0;
	while (i < lem_in->paths_count + 1)
	{
		if (i == lem_in->paths_count)
			i = 0;
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
				path_copy(lem_in, paths, optimun);
			}
		}
		i = return_path_len(lem_in, paths, unique, i);
	}
}

/*
*	Calculate the shortest paths with least amount of turns to move the 
*	ants throught. Special cases.
*	1. One path 2. One ant
*/
void	calculate_optimal_paths(t_lem_in *lem_in)
{
	t_path	**paths;
	t_path	**optimun;
	int		min_turns;
	int		start_neigbors;

	start_neigbors = calculate_neigbors(lem_in);
	paths = create_paths(lem_in, (size_t)start_neigbors);
	optimun = create_paths_empty((size_t)start_neigbors);
	path_copy(lem_in, paths, optimun);
	min_turns = calculate_path_turns(lem_in, paths);
	if (lem_in->paths_count != 1 && start_neigbors != 1)
	{
		if (lem_in->ants_count != 1)
		{
			calculate_optimal_paths_extend(lem_in, paths, optimun, min_turns);
		}
	}
	free(paths);
	free_paths(lem_in);
	lem_in->paths = optimun;
	lem_in->paths_count = (int)count_paths(lem_in->paths);
}
