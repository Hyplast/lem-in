/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_ants(t_lem_in *lem_in)
{
	int	ants;

	ants = 1;
	while (lem_in->ants_count >= ants)
	{
		lem_in_add_ant(lem_in, ants);
		ants++;
	}
}

/*
*	Calculate lenght of the string array
*/
int	lenght_of_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

/*
*   Check if string is a number
*/
int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/*
*	Use bubble sorting to sort the paths in length ascending order.
*/
void 	bubble_sort_paths(t_lem_in *lem_in)
{
	t_path	**paths;
	t_path	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	paths = lem_in->paths;
	while(lem_in->paths[i])
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