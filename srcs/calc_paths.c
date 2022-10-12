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
	if (++times_called >= max_times_called - 1)
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

void	next_path_copy(t_path **copy, t_path *paths)
{
	t_path	*path;
	t_path	*new;
	t_path	*temp;

	temp = paths;
	if (paths == NULL)
	{
		free(*copy);
		*copy = NULL;
		return ; 
	}
	new = (t_path *)malloc(sizeof(t_path));
	new->room = temp->room;
	new->turns = temp->turns;
	new->path_length = temp->path_length;
	new->ants = temp->ants;
	*copy = new;
	path = *copy;
	temp = temp->next_path;
	while (temp)
	{
		new = (t_path *)malloc(sizeof(t_path));
		new->room = temp->room;
		new->turns = temp->turns;
		new->path_length = temp->path_length;
		new->ants = temp->ants;
		path->next_path = new;
		path = path->next_path;
		temp = temp->next_path;
	}
	path->next_path = NULL;
}

void	path_copy(t_lem_in *lem_in, t_path **paths, t_path **copy)
{
	int	i;
	int	start_neigbors;

	start_neigbors = calculate_neigbors(lem_in);

	i = 0;
	while (i < start_neigbors)
	{
		free_a_path(copy[i]);
		next_path_copy(&copy[i], paths[i]);
		i++;
	}
}

/*
*	Helper function for calculate optimal paths.
*	Keep the best shortest turn combination stored in optimun
*	
*/
void	calculate_optimal_paths_extend(t_lem_in *lem_in, t_path **paths,
			t_path **optimun, int min_turns)
{
	int	recent_turns;
	int		i;
	int		unique;

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
	// path_copy(lem_in, optimun, paths);
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
		}
		j = 0;
		i++;
	}
	free(lem_in->paths);
	lem_in->paths = NULL;
}


/*
*	@param1	Number of paths
*	@return paths array with shortest path at index [0]
*/
t_path	**create_paths_empty(size_t size)
{
	t_path	**paths;
	// t_path	*path;
	size_t	i;

	i = 0;
	paths = (t_path **)malloc(sizeof(t_path *) * (size + 1));
	while (i <= size)
	{
		paths[i++] = NULL;
	}
	return (paths);
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
			calculate_optimal_paths_extend(lem_in, paths, optimun, min_turns);
	}
	free(paths);
	free_paths(lem_in);
	lem_in->paths = optimun;
	lem_in->paths_count = (int)count_paths(lem_in->paths);
}
