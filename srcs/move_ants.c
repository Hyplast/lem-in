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
				check_end_and_visited(lem_in, path, ant);
		}
		path = temp;
		ant = ant->next;
	}
}

void	move_ants_from_start_other_paths(t_lem_in *lem_in, t_path *path)
{
	t_ant	*ant;
	t_path	*temp;

	temp = path;
	ant = lem_in->ants;
	while (ant != NULL)
	{
		while (path && path->room != ant->room)
			path = path->next_path;
		if (path && ant->room != lem_in->end_room)
		{
			if (path->next_path->room == lem_in->end_room)
				set_end(lem_in, ant);
			else if (path->next_path->room->visited == 0)
			{
				if (ant->room == lem_in->start_room)
					lem_in->ants_in_start--;
				ant->room = path->next_path->room;
				ant->room->visited = 1;
				print_ant_move(ant->ant_id, ant->room->name);
			}
		}
		path = temp;
		ant = ant->next;
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
				set_end(lem_in, ant);
			else if (path->next_path->room->visited == 0)
			{
				if (ant->room == lem_in->start_room)
					lem_in->ants_in_start--;
				ant->room = path->next_path->room;
				ant->room->visited = 1;
				print_ant_move(ant->ant_id, ant->room->name);
			}
		}
		path = temp;
		ant = ant->next;
	}
}

/*
*	Move other ants than the shortest path.
*	Only send ants to longer paths if 
*	ants in start > path length difference 
*/
void	move_others(t_lem_in *lem_in, t_path *path)
{
	int	sum;

	if (lem_in->paths[0] != path)
	{
		if (lem_in->ants_in_start > 0)
		{
			sum = sum_of_path_differences(lem_in, path);
			if (lem_in->ants_in_start > sum)
				move_ants_from_start_other_paths(lem_in, path);
			else
				mov_ants_oth_rooms_by_oth_paths(lem_in, path);
		}
		else
			mov_ants_oth_rooms_by_oth_paths(lem_in, path);
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
			move_others(lem_in, path);
			path = lem_in->paths[++i];
		}
		set_visited_to_zero(lem_in);
		i = 0;
		path = lem_in->paths[i];
		remove_ants_in_goal(lem_in);
		ft_putchar('\n');
		counter++;
	}
	ft_putstr("Number of lines: ");
	ft_putnbr(counter);
	ft_putchar('\n');
}
