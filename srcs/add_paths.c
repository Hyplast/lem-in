/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	@param1	Number of paths
*	@return paths array with shortest path at index [0]
*/
t_path	**create_paths_empty(size_t size)
{
	t_path	**paths;
	size_t	i;

	i = 0;
	paths = (t_path **)malloc(sizeof(t_path *) * (size + 1));
	while (i <= size)
	{
		paths[i++] = NULL;
	}
	return (paths);
}

void	free_non_used_paths(t_lem_in *lem_in, t_path **new_paths) // REMOVE IF UN-USED !!
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

t_path	*init_path_copy(t_path *copy_path)
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	new->room = copy_path->room;
	new->turns = copy_path->turns;
	new->path_length = copy_path->path_length;
	new->ants = copy_path->ants;
	return (new);
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
	new = init_path_copy(temp);
	*copy = new;
	path = *copy;
	temp = temp->next_path;
	while (temp)
	{
		new = init_path_copy(temp);
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
