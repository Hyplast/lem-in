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
