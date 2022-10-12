/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_paths_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/08/29 00:54:39 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	Calculate sum of length of the paths
*	@return (int) Sum of paths lengths
*/
int	total_path_len(t_path **paths)
{
	int	i;
	int	paths_len_sum;

	i = 0;
	paths_len_sum = 0;
	while (paths[i] != NULL)
		paths_len_sum += paths[i++]->path_length;
	return (paths_len_sum);
}

void	set_up_ants_for_paths(t_lem_in *lem_in, t_path **paths, size_t n_paths)
{
	int		i;
	int		ants;
	int		total_ants;

	i = 0;
	total_ants = 0;
	ants = lem_in->ants_count / (int)n_paths;
	while (paths[i])
	{
		total_ants = total_ants + ants;
		paths[i++]->ants = ants;
	}
	while (total_ants < lem_in->ants_count)
	{
		paths[0]->ants++;
		total_ants++;
	}
}

void	increment_lowest_decrease_highest(t_path **paths)
{
	int		i;
	int		lowest;
	int		highest;
	int		low_i;
	int		high_i;

	lowest = 2147483647;
	highest = -2147483648;
	i = -1;
	while (paths[++i])
	{
		paths[i]->turns = paths[i]->ants + paths[i]->path_length - 1;
		if (paths[i]->turns > highest)
		{
			highest = paths[i]->turns;
			high_i = i;
		}
		if (paths[i]->turns < lowest)
		{
			lowest = paths[i]->turns;
			low_i = i;
		}
	}
	paths[low_i]->ants = paths[low_i]->ants + 1;
	paths[low_i]->turns = paths[low_i]->ants + paths[low_i]->path_length - 1;
	paths[high_i]->ants = paths[high_i]->ants - 1;
	paths[high_i]->turns = paths[high_i]->ants + paths[high_i]->path_length - 1;
}

int		get_paths_total_turns(t_path **paths)
{
	int	i;
	int	turns;
	int result;

	turns = -1;
	result = -1;
	i = -1;
	while (paths[++i])
	{
		result = paths[i]->ants + paths[i]->path_length - 1;
		paths[i]->turns = result;
		if (result > turns)
			turns = result;
	}
	return (turns);
}

int	calculate_path_turns(t_lem_in *lem_in, t_path **paths)
{
	int		lowest;
	int		turns;
	size_t	n_paths;
	size_t	i;

	i = 0;
	n_paths = count_paths(paths);
	if (n_paths == 1)
		return ((lem_in->ants_count + paths[0]->path_length - 1));
	set_up_ants_for_paths(lem_in, paths, n_paths);
	turns = get_paths_total_turns(paths);
	while (i < 1)
	{
		lowest = turns;
		increment_lowest_decrease_highest(paths);
		increment_lowest_decrease_highest(paths);
		increment_lowest_decrease_highest(paths);
		increment_lowest_decrease_highest(paths);
		increment_lowest_decrease_highest(paths);
		turns = get_paths_total_turns(paths);
		if (turns >= lowest)
			i = 1;
	}
	return (lowest);
}
