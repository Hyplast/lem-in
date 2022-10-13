/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_paths_big.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/08/29 00:54:39 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*/
void	select_paths(t_lem_in *lem_in, t_path **paths, int select[1000])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (select[i] != -2)
	{
		if (select[i] != -1)
		{
			paths[j++] = lem_in->paths[select[i]];
		}
		i++;
	}
	paths[j] = NULL;
}

int	increase_number(int select[1000], int max)
{
	int	i;

	i = 0;
	while (select[i] != -2)
	{
		if (select[i] < max)
		{
			select[i] =+ 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	calculate_optimal_paths_extend_v2(t_lem_in *lem_in, t_path **paths,
			t_path **optimun, int min_turns)
{
	int	paths_count;
	int	start_neigbors;
	int	selection_array[1000];
	int	i;
	int		unique;
	int	recent_turns;
	int	result;
	i = 0;
	start_neigbors = calculate_neigbors(lem_in);
	while (i < start_neigbors)
		selection_array[i++] = -1;
	selection_array[i] = -2;
	result = increase_number(selection_array);
	// paths_count = (int)count_paths(paths);
	while (result == 1)
	{
		while (unique == 0)
		{
			select_paths(lem_in, paths, selection_array);
			unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
			
		}
		recent_turns = calculate_path_turns(lem_in, paths);
		if (recent_turns < min_turns)
		{
			min_turns = recent_turns;
			path_copy(lem_in, paths, optimun);
		}
		result = increase_number(selection_array);
	}
	
	// ON GOING: kEEp index which values have passed.



	unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
	add_path_to_paths(paths, lem_in->paths[i]);
	remove_path_from_paths(lem_in, paths);

}
*/

void	check_for_optimal_paths(t_lem_in *lem_in, t_path **paths)
{
	int	turns;
	int	optimun_turns;

	turns = calculate_path_turns(lem_in, paths);
	optimun_turns = calculate_path_turns(lem_in, lem_in->optimun);
	if (optimun_turns > turns)
	{
		path_copy(lem_in, paths, lem_in->optimun);
		// lem_in->optimun = paths;
	}
		
}

/* arr[]  ---> Input Array							->	lem_in->paths
   n      ---> Size of input array 					->	lem_in->paths_count
   r      ---> Size of a combination to be printed	->	size = 1 + count_paths(optimun);
   index  ---> Current index in data[]				-> 	lem_in->index
   data[] ---> Temporary array to store current combination
   i      ---> index of current element in arr[]     */
void combinationUtil(t_lem_in *lem_in, t_path **paths, int index, int i)
{
	int	res;
	
	// Current combination is ready, print it
	if (index == lem_in->r)
	{
		res = compare_all_paths_unique_itself(lem_in, paths);
		if (res == 1)
			check_for_optimal_paths(lem_in, paths);
		for (int j=0; j<lem_in->r; j++)
			printf("%s->%s:%d ", paths[j]->next_path->room->name, paths[j]->next_path->next_path->room->name, paths[j]->path_length);
		printf("\n");
		return;
	}
 
	// When no more elements are there to put in data[]
	if (i >= lem_in->paths_count)
		return;
 
	// current is included, put next at next location
	paths[index] = lem_in->paths[i];
	combinationUtil(lem_in, paths, index+1, i+1);
 
    // current is excluded, replace it with next (Note that
    // i+1 is passed, but index is not changed)
	combinationUtil(lem_in, paths, index, i+1);
}

// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void get_combinations(t_lem_in *lem_in, t_path **paths, int r)
{
    // A temporary array to store all combination one by one
    // int data[100];
	// int	start_neigbors;
	int	i;
	int	index;

	i = 0;
	index = 0;
	lem_in->r = r;
	// start_neigbors = calculate_neigbors(lem_in);
	// while (i < start_neigbors)
	// 	data[i++] = -1;
	// data[i] = -2;
 
    // Print all combination using temporary array 'data[]'
    combinationUtil(lem_in, paths, index, i);
}

int		find_best_paths_size(t_lem_in *lem_in, t_path **paths,
			int n_paths, int turns)
{
	// int	unique;
	// int	i;
	// int	j;
	// int	recent_turns;
	// int	min_turns;
	// int	turns_improved;

	// i = 0;
	// j = 1;
	// turns_improved = optimun[0]->turns;
	// min_turns = paths[0]->turns;
	// while (turns_improved < )
	// recent_turns = lem_in->optimun[0]->turns;
	lem_in->paths_count = (int)count_paths(lem_in->paths);
	// lem_in->n = count_paths(lem_in->paths);
	get_combinations(lem_in, paths, n_paths);

	if (lem_in->optimun[0]->turns < turns)
		return (1);
	return (0);
	// if (turns_improved >)

	// unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
	// while (j < n_paths)
	// {
		
	// 	while (unique == 0 && lem_in->paths[++i] != NULL)
	// 		unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
	// 	if (unique == 1)
	// 	{
	// 		add_path_to_paths(paths, lem_in->paths[i]);
	// 		recent_turns = calculate_path_turns(lem_in, paths);
	// 		if (recent_turns < min_turns)
	// 		{
	// 			min_turns = recent_turns;
	// 			path_copy(lem_in, paths, optimun);
	// 		}
	// 	}
	// 	i = j++;
	// }
}

/*
*	Calculate bigger number of path combinations throught
*	compared to previously found. Increase the 
*/
void	calculate_big_n_of_paths(t_lem_in *lem_in, t_path **paths,
			t_path **optimun, int min_turn)
{
	int	size;
	int	start_neigbors;
	int	found;

	found = 1;
	size = (int)count_paths(optimun);
	start_neigbors = calculate_neigbors(lem_in);
	lem_in->optimun = create_paths_empty((size_t)start_neigbors);
	path_copy(lem_in, optimun, lem_in->optimun);
	// lem_in->optimun = optimun;
	while (size < start_neigbors && found == 1)
	{
		found = find_best_paths_size(lem_in, paths, ++size, optimun[0]->turns);
		if (found == 1)
		{
			if (lem_in->optimun[0]->turns < min_turn)
				path_copy(lem_in, lem_in->optimun, optimun);
		}
	}

	// void	set_lem_in_paths_to_best(t_lem_in *lem_in, )
}
