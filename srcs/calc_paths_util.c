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