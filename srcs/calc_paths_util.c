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

void	add_path_to_paths(t_path **paths, t_path *path)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	paths[i] = path;
}

int	remove_path_from_paths(t_lem_in *lem_in, t_path **paths)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (paths[i] != NULL)
	{
		i++;
	}
	i--;
	while (paths[i] != lem_in->paths[j])
		j++;
	paths[i] = NULL;
	return (j);
}

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
	lowest = ((float)paths[0]->path_length / (float)paths_len_sum
			* (float)lem_in->ants_count);
	lowest = lowest + (float)paths[1]->path_length - 1;
	return (lowest);
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
