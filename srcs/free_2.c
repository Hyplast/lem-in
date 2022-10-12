/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_paths_separate(t_path **free_paths)
{
	t_path	*path;
	t_path	*paths;
	t_path	*temp;
	int		i;

	i = 0;
	if (free_paths == NULL)
		return ;
	paths = free_paths[i];
	while (paths)
	{
		path = paths->next_path;
		while (path)
		{
			temp = path->next_path;
			free(path);
			path = temp;
		}
		free(paths);
		paths = free_paths[++i];
	}
	free(free_paths);
	free_paths = NULL;
}

void	free_a_path(t_path *path)
{
	t_path	*temp;

	temp = path;
	while (temp)
	{
		path = temp;
		temp = path->next_path;
		free(path);
		path = NULL;
	}
}

void	free_a_path_from_lem_in(t_lem_in *lem_in, t_path *path)
{
	int		i;

	i = 0;
	while (lem_in->paths[i] != path)
		i++;
	free_a_path(path);
	lem_in->paths[i] = NULL;
}

void	free_paths_array_only(t_lem_in *lem_in)
{
	t_path	*paths;
	int		i;

	i = 0;
	if (lem_in->paths == NULL)
		return ;
	paths = lem_in->paths[i];
	while (paths)
	{
		free(paths);
		paths = NULL;
		paths = lem_in->paths[++i];
	}
	free(lem_in->paths);
	lem_in->paths = NULL;
}
