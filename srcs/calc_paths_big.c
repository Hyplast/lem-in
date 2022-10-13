/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_paths_big.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/08/29 00:54:39 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_for_optimal_paths(t_lem_in *lem_in, t_path **paths)
{
	int	turns;
	int	optimun_turns;

	turns = calculate_path_turns(lem_in, paths);
	optimun_turns = calculate_path_turns(lem_in, lem_in->optimun);
	if (optimun_turns > turns)
	{
		path_copy(lem_in, paths, lem_in->optimun);
	}
}

void	combination_util(t_lem_in *lem_in, t_path **paths, int index, int i)
{
	int	res;

	if (index == lem_in->r)
	{
		res = compare_all_paths_unique_itself(lem_in, paths);
		if (res == 1)
			check_for_optimal_paths(lem_in, paths);
		return ;
	}
	if (i >= lem_in->paths_count)
		return ;
	paths[index] = lem_in->paths[i];
	combination_util(lem_in, paths, index + 1, i + 1);
	combination_util(lem_in, paths, index, i + 1);
}

void	get_combinations(t_lem_in *lem_in, t_path **paths, int r)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	lem_in->r = r;
	combination_util(lem_in, paths, index, i);
}

int	find_best_paths_size(t_lem_in *lem_in, t_path **paths,
			int n_paths, int turns)
{
	lem_in->paths_count = (int)count_paths(lem_in->paths);
	get_combinations(lem_in, paths, n_paths);
	if (lem_in->optimun[0]->turns < turns)
		return (1);
	return (0);
}

/*
*	Calculate bigger number of path combinations throught
*	compared to previously found. Increase the 
*/
void	calculate_big_n_of_paths(t_lem_in *lem_in, t_path **paths,
			t_path **optimun, int min_turns)
{
	int	size;
	int	start_neigbors;
	int	found;

	found = 1;
	min_turns = calculate_path_turns(lem_in, optimun);
	size = (int)count_paths(optimun);
	start_neigbors = calculate_neigbors(lem_in);
	lem_in->optimun = create_paths_empty((size_t)start_neigbors);
	path_copy(lem_in, optimun, lem_in->optimun);
	while (size < start_neigbors && found >= 1)
	{
		found = find_best_paths_size(lem_in, paths, ++size, min_turns);
		if (found == 1)
		{
			if (lem_in->optimun[0]->turns < min_turns)
				path_copy(lem_in, lem_in->optimun, optimun);
			return ;
		}
	}
}
