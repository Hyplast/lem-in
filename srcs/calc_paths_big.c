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

int		find_best_paths_size(t_lem_in *lem_in, t_path **paths,
			t_path **optimun, int n_paths)
{
	int	unique;
	int	i;
	int	j;
	int	recent_turns;
	int	min_turns;

	i = 0;
	j = 1;
	min_turns = 9999;
	unique = check_all_paths_uniq(lem_in, lem_in->paths[i], paths);
	while (j < n_paths)
	{
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
		i = j++;
	}
}

void	calculate_optimal_paths_extend_v3(t_lem_in *lem_in, t_path **paths,
			t_path **optimun, int min_turn)
{
	int	size;
	int	start_neigbors;
	int	found;

	found = 1;
	size = 1;
	start_neigbors = calculate_neigbors(lem_in);
	while (size < start_neigbors && found == 1)
	{
		found = find_best_paths_size(lem_in, paths, optimun, size++);
	}
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



void combinationUtil(int arr[],int n,int r,int index,int data[],int i);
 
// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void printCombination(int arr[], int n, int r)
{
    // A temporary array to store all combination one by one
    int data[100];
	int	start_neigbors;
	int	i;

	i = 0;
	start_neigbors = calculate_neigbors(lem_in);
	while (i < start_neigbors)
		data[i++] = -1;
	data[i] = -2;
 
    // Print all combination using temporary array 'data[]'
    combinationUtil(arr, n, r, 0, data, 0);
}
 
/* arr[]  ---> Input Array
   n      ---> Size of input array
   r      ---> Size of a combination to be printed
   index  ---> Current index in data[]
   data[] ---> Temporary array to store current combination
   i      ---> index of current element in arr[]     */
void combinationUtil(int arr[], int n, int r, int index, int data[], int i)
{
    // Current combination is ready, print it
    if (index == r)
    {
		res = compare_all_paths_unique(lem_in, paths1, paths2);
		if (res == 1)
		{
			
		}
        for (int j=0; j<r; j++)
            printf("%d ",data[j]);
        printf("\n");
        return;
    }
 
    // When no more elements are there to put in data[]
    if (i >= n)
        return;
 
    // current is included, put next at next location
    data[index] = arr[i];
    combinationUtil(arr, n, r, index+1, data, i+1);
 
    // current is excluded, replace it with next (Note that
    // i+1 is passed, but index is not changed)
    combinationUtil(arr, n, r, index, data, i+1);
}

