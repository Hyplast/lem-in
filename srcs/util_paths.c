/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_paths.c                                       :+:      :+:    :+:   */
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
t_path	**create_paths(t_lem_in *lem_in, size_t	size)
{
	t_path	**paths;
	t_path	*path;

	paths = (t_path **)malloc(sizeof(t_path *) * (size + 1));
	path = get_shortest_path(lem_in);
	printf("-added path:%dlength;%s;%s-\n", path->path_length, path->next_path->room->name, path->next_path->next_path->room->name);
	paths[0] = path;
	paths[1] = NULL;
	return (paths);
}

/*
*	Use bubble sorting to sort the paths in length ascending order.
*/
void	bubble_sort_paths(t_lem_in *lem_in)
{
	t_path	**paths;
	t_path	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	paths = lem_in->paths;
	while (lem_in->paths[i])
	{
		while (paths[j])
		{
			if (lem_in->paths[i]->path_length < paths[j]->path_length)
			{
				temp = paths[j];
				paths[j] = lem_in->paths[i];
				lem_in->paths[i] = temp;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

/*
*	@return Shortest path from lem-in paths.
*/
t_path	*get_shortest_path(t_lem_in *lem_in)
{
	t_path	*path;
	t_path	*temp;
	int		i;

	i = 0;
	temp = lem_in->paths[i];
	path = temp;
	while (temp)
	{
		if (path->path_length > temp->path_length)
			path = temp;
		temp = lem_in->paths[++i];
	}
	return (path);
}
