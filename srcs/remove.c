/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	Remove ant from lem_in
*	@param Lem_in
*	@param Ant to be removed.
*/
void	remove_ant_from_lem_in(t_lem_in *lem_in, t_ant *ant)
{
	t_ant	*temp;

	temp = lem_in->ants;
	if (temp == ant)
	{
		if (temp->next == NULL)
			lem_in->ants = NULL;
		else
			lem_in->ants = temp->next;
	}
	else
	{
		while (temp->next != ant)
			temp = temp->next;
		if (temp->next->next == NULL)
			temp->next = NULL;
		else
			temp->next = temp->next->next;
	}
	free(ant);
	ant = lem_in->ants;
}

void	remove_ants_in_goal(t_lem_in *lem_in)
{
	t_ant	*ant;

	ant = lem_in->ants;
	while (ant)
	{
		if (ant->room == lem_in->end_room)
		{
			remove_ant_from_lem_in(lem_in, ant);
			ant = lem_in->ants;
		}
		else
			ant = ant->next;
	}
}

int	remove_last_path(t_lem_in *lem_in, t_path **paths)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (paths[i] != NULL)
		i++;
	while (lem_in->paths[j] != paths[i - 1])
		j++;
	paths[i - 1] = NULL;
	return (j);
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
*	Remove path n from lem_in
*/
void	remove_path_n(t_lem_in *lem_in, int to_be_removed)
{
	t_path	**paths;
	int		i;
	int		j;

	i = 0;
	j = 0;
	paths = init_paths(count_paths(lem_in->paths));
	while (lem_in->paths[i])
	{
		if (to_be_removed != i)
		{
			paths[j++] = lem_in->paths[i];
		}
		else
			free_a_path_from_lem_in(lem_in, lem_in->paths[i]);
		i++;
	}
	paths[j] = NULL;
	free(lem_in->paths);
	lem_in->paths = paths;
}
