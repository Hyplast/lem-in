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

/*
*	Calculate shortest paths for ants. Max paths is whichever is lower, amount of 
*	neighbors of start or end rooms. Replace paths in ascending order into lem-in.
*	TODO: add start_neighbors and end_neighbors and update paths_count to lem_in.
*/
void	calculate_optimal_paths(t_lem_in *lem_in)
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
