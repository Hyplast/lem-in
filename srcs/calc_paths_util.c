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
*	Check which paths have already been tried and keep count
*	on them to not to try them again.
*/
int	check_and_add(t_lem_in *lem_in, t_path *path_1,
	t_path **paths, int replace[100])
{
	int	unique;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (replace[j] != -1)
	{
		if (path_1 == lem_in->paths[replace[j++]])
			return (0);
	}
	unique = check_all_paths_uniq(lem_in, path_1, paths);
	if (unique == 1)
	{
		i = (int)count_paths(paths);
		paths[i] = path_1;
		paths[i + 1] = NULL;
	}
	return (unique);
}

/*
*	Loop throught all paths to try find size amount of unique paths
*	combinations.
*/
int	find_permuntations(t_lem_in *lem_in, t_path **paths, int size)
{
	int		unique;
	int		i;
	int		j;
	int		k;
	int		tried[100];

	i = 0;
	j = 0;
	k = 0;
	while (i < 100)
		tried[i++] = -1;
	i = 0;
	paths[j++] = lem_in->paths[i];
	while (j < size)
	{
		unique = check_and_add(lem_in, lem_in->paths[i], paths, tried);
		while (unique == 0 && (i < lem_in->paths_count - 1))
			unique = check_and_add(lem_in, lem_in->paths[++i], paths, tried);
		if (unique == 1)
		{
			i = 0;
			while (i < 100)
				tried[i++] = -1;
			j++;
			k = 0;
		}
		else
		{
			tried[k++] = remove_last_path(lem_in, paths);
			j--;
		}
		i = min_number(lem_in->paths_count, tried);
	}
	return (1);
}

/*
*	Calculate sum of length of the paths
*	@return (int) Sum of paths lengths
*/
int		total_path_len(t_path **paths)
{
	int	i;
	int	paths_len_sum;

	i = 0;
	paths_len_sum = 0;
	while(paths[i] != NULL)
		paths_len_sum += paths[i++]->path_length;
	return (paths_len_sum);
}

/*
*	Calculate amount turns for the path to walk the ants through.
*	@return (float) number of turns
*/
float	calculate_path_turns(t_lem_in *lem_in, t_path **paths)
{
	int		paths_len_sum;
	float	lowest;
	size_t	n_paths;

	n_paths = count_paths(paths);
	if (n_paths == 1)
		return ((float)(lem_in->ants_count + paths[0]->path_length - 1));
	paths_len_sum = total_path_len(paths);
	lowest = ((float)paths[0]->path_length / (float)paths_len_sum * (float)lem_in->ants_count);
	lowest = lowest + (float)paths[1]->path_length - 1;
	return (lowest);
}

void	check_other_than_shortest(t_lem_in *lem_in, t_path **paths,
			int max_neigbors)
{
	// int	i;
	// int	j;
	int		paths_len_sum;
	float	lowest;

	// i = 0;
	// j = 0;
	paths_len_sum = total_path_len(paths);
	lowest = ((float)paths[0]->path_length / (float)paths_len_sum * (float)lem_in->ants_count);
	lowest = lowest + (float)paths[0]->path_length - 1;
	
	while (max_neigbors < (int)count_paths(paths))
	if ((float)paths_len_sum < lowest)
	{
		// swap_to_new_path();
	}
	/*11 ants

	4 lenght
	12 length

	5 + 6 = 11
	4 + 12 = 16

	11 - 5 = 5/11 = 
	11 - 6 = 6/11 = 

	16 - 4 = 4/16  = 1 /4
	16 - 12 = 12/16 = 3 / 4

	2,75 -> ants -> 3 ants + 12 - 1 -> 14 turns
				->	2 ants + 12 - 1 -> 13 turns
	8,25 -> ants -> 9 ants + 4  - 1 -> 12 turns
				->	8 ants + 4  - 1 -> 11 turns


	11 ants = 6 ants -> 6 + 5 - 1 -> 10 turns
			= 6 ants -> 5 + 6 - 1 -> 10 turns
			= 5 ants -> 
	pathslength + ants - 1 = turns
	6 + 11 - 1 = 16 turns 
	5 + 11 - 1 =  15 turns

	12 + 2 - 1 = 13 turns 
	4 + 9 - 1 =  12 turns
 
  turn 4, 1
turn 5, 2
turn 6, 3
turn 7, 4
turn 8, 5
turn 9, 6
turn 10, 7
turn 11, 8
turn 12, 9
turn 13, 10

	pathlength 5 + 6 = 11

	5/11 6/11 	-> 5 ants
				-> 6 ants -> 6 + 

*/
}




/*
*	Check if amount of neigbors == shortest paths
*/
void	check_for_max_neigbor_option(t_lem_in *lem_in, t_path **paths,
	int max_neigbors)
{
	int		j;
	int		n_paths;
	t_path	**compare;
	int		start_neigbors;

	j = 0;
	check_other_than_shortest(lem_in, paths, max_neigbors);
	start_neigbors = calculate_neigbors(lem_in);
	n_paths = (int)count_paths(paths);
	if (n_paths < max_neigbors)
	{
		compare = paths;
		while (j == 0)
			j = find_permuntations(lem_in, compare, start_neigbors--);
		if (start_neigbors > n_paths)
			paths = compare;
	}
	lem_in->paths = paths;
	lem_in->paths_count = (int)count_paths(lem_in->paths);
}



/*
*	Return whichever has lower amount of neighbors, start or end room.
*/
int	calculate_neigbors(t_lem_in *lem_in)
{
	int		start_neigbors;
	int		end_neigbors;

	start_neigbors = (int)ft_lstlen(lem_in->start_room->neighbors);
	end_neigbors = (int)ft_lstlen(lem_in->end_room->neighbors);
	if (start_neigbors > end_neigbors)
		start_neigbors = end_neigbors;
	return (start_neigbors);
}