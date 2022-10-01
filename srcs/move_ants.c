/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/08/29 00:54:39 by severi           ###   ########.fr       */
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
	// ft_printf("L%i-%s ", ant->ant_id, lem_in->end_room->name);
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

/*
*	move ants from other rooms by other paths
*/
void	mov_ants_oth_rooms_by_oth_paths(t_lem_in *lem_in, t_path *path)
{
	t_ant	*ant;
	t_path	*temp;

	path = path->next_path;
	temp = path;
	ant = lem_in->ants;
	while (ant != NULL)
	{
		if (ant->room != lem_in->end_room && ant->room != lem_in->start_room)
		{
			while (path && path->room != ant->room)
				path = path->next_path;
			if (path)
			{
				if (path->room == lem_in->end_room)
				{
					ft_printf("L%i-%s ", ant->ant_id, ant->room->name);
					ant->room = lem_in->end_room;
				}
				else if (path->next_path->room->visited == 0)
				{
					ant->room = path->next_path->room;
					ant->room->visited = 1;
					ft_printf("L%i-%s ", ant->ant_id, ant->room->name);
				}
			}
		}
		path = temp;
		ant = ant->next;
	}
}

void	move_ants_from_start_other_paths(t_lem_in *lem_in, t_path *path)
{
	t_ant	*ant;

	ant = lem_in->ants;
	while (ant && ant->room != lem_in->start_room)
	{
		ant = ant->next;
	}
	if (ant)
	{
		if (ant->room == lem_in->start_room)
		{
			ant->room = path->next_path->room;
			ant->room->visited = 1;
			ft_printf("L%i-%s ", ant->ant_id, ant->room->name);
			lem_in->ants_in_start--;
		}
	}
}

void	move_ants_by_shortest_path(t_lem_in *lem_in, t_path *path)
{
	t_ant	*ant;
	t_path	*temp;

	temp = path;
	ant = lem_in->ants;
	while (ant != NULL)
	{
		while (path && path->room != ant->room)
			path = path->next_path;
		if (path)
		{
			if (path->room == lem_in->end_room)
			{
				ft_printf("L%i-%s ", ant->ant_id, ant->room->name);
				ant->room = lem_in->end_room;
			}
			else if (path->next_path->room->visited == 0)
			{
				if (ant->room == lem_in->start_room)
					lem_in->ants_in_start--;
				ant->room = path->next_path->room;
				ant->room->visited = 1;
				ft_printf("L%i-%s ", ant->ant_id, ant->room->name);
			}
		}
		path = temp;
		ant = ant->next;
	}
}

/*	Go through the ants.
*	Take the first ant, put it into next room. This room is now 
*	occupied unless end room. Print it
*	Take the second ant, if there is more than one path, compare it to N, 
*	if bigger take the second path. When ants cant move anymore because all 
*	next rooms are occupied, increase turn, print \n and go back to start
*	if ant = end room, remove from the ant list.
*	Continue until all ants are in end room.
*/
void	move_ants(t_lem_in *lem_in)
{
	t_path	*path;
	int		i;
	int		counter;

	counter = 0;
	i = 0;
	path = lem_in->paths[i];
	while (lem_in->ants)
	{
		while (path)
		{
			if (path == lem_in->paths[0])
				move_ants_by_shortest_path(lem_in, path);
			else if (path->path_length < lem_in->ants_in_start - 1)
				move_ants_from_start_other_paths(lem_in, path);
			if (path != lem_in->paths[0])
				mov_ants_oth_rooms_by_oth_paths(lem_in, path);
			path = lem_in->paths[++i];
		}
		set_visited_to_zero(lem_in);
		i = 0;
		path = lem_in->paths[i];
		remove_ants_in_goal(lem_in);
		ft_printf("\n");
		counter++;
	}
	ft_printf("Number of lines: %d\n", counter);
}
