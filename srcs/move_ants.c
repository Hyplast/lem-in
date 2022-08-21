/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/08/13 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    init_ants(t_lem_in *lem_in)
{
    int     ants;
    // t_ant   *ant;
 
    ants = 1;
    while (lem_in->ants_count >= ants)
    {
        lem_in_add_ant(lem_in, ants);
        ants++;
        // ant = (t_ant *)malloc(sizeof(t_ant));
        // ant->ant_id = ants;
        // ant->room = lem_in->start_room;
        // ants++;
        // ant->next = ant;
        // lem_in->ants = ant;
    }
}

void	remove_first_ant(t_lem_in *lem_in)
{
	t_ant	*ant;

	ant = lem_in->ants;
	if (lem_in->ants != NULL)
		lem_in->ants = lem_in->ants->next;
	free(ant);
}

void	ant_is_in_goal(t_lem_in *lem_in)
{
	if (lem_in->ants->room == lem_in->end_room)
		remove_first_ant(lem_in);
}


void	move_all_ants_on_one_path_by_one(t_lem_in *lem_in, t_path *path)
{
	t_ant *ant;
	t_path	*temp;

	temp = path;
	ant = lem_in->ants;
	while(ant != NULL)
	{
		while(path && path->room != ant->room)
			path = path->next_path;
		if (path)
		{
			if (path->room == lem_in->end_room)
				ft_printf("L%i-%s ", ant->ant_id, path->room->name);
			else if (path->next_path->room->visited == 0)
			{
				ant->room = path->next_path->room;
				ant->room->visited = 1;
				ft_printf("L%i-%s ", ant->ant_id, ant->room->name);
			}
			// path = path->next_path;
		}
		path = temp;
		ant = ant->next;
	}
}

// void	traverse_ants_throught_path(t_lem_in *lem_in, t_path *path)
// {
// 	t_ant *ant;

// 	ant = lem_in->ants;

// 	ft_printf("L%i-%s ", ant->ant_id, ant->room->name);
// }


/*
*	Move ants one turn at a time. Print moves each turn..
*/
void    move_ants(t_lem_in *lem_in)
{
    // t_move  *move;
    // t_path  *path;
	// t_ant	*ant;
	// int		turn;
	// t_path	*temp;
	t_path	*path;
	// turn = 0;
   
	int		i;
	i = 0;
	path = lem_in->paths[i];
    // init_ants(lem_in);
	// lem_in->paths_count;
	
	/*	Go through the ants.
	*	Take the first ant, put it into next room. This room is now occupied unless end room.
	*	Print it
	*	Take the second ant, if there is more than one path, compare it to N, if bigger take the second path
	*	When ants cant move anymore because all next rooms are occupied, increase turn, print \n and go back to start
	*	if ant = end room, remove from the ant list.
	*	Continue until all ants are in end room.
	*/
	while(lem_in->ants)
	{
		while (path)
		{
			move_all_ants_on_one_path_by_one(lem_in, path);
			path = lem_in->paths[++i];
		}
		set_visited_to_zero(lem_in);
		i = 0;
		path = lem_in->paths[i];
		if (lem_in->ants->room == lem_in->end_room)
			ant_is_in_goal(lem_in);
		ft_printf("\n");
	}
	// move_all_ants_on_one_path_by_one(lem_in, path);
	// path = lem_in->paths[i++];
	// move_all_ants_on_one_path_by_one(lem_in, path);
	// ft_printf("\n");
	// // path = lem_in->paths[i++];
	// move_all_ants_on_one_path_by_one(lem_in, path);

	/*
	while (lem_in->ants)
	{
		ant = lem_in->ants;
		while (ant != NULL)
		{
			temp = path;
			while (temp != NULL)
			{
				ft_printf("Turn %d, ant %d is moving to %s ->", turn, ant->ant_id, path->room->name);

				// if (path->room == ant->room)
				// {
				// 	ft_printf("%s\n", path->room->name);
				// 	ant->room = path->next_path->room;
				// 	turn++;
				// }
				temp = temp->next_path;
			}
			path = lem_in->paths[i++];
			ant = ant->next;
		}
		turn++;
		ft_printf("\n");
	}
	
			if (ant->room->visited == 1)
		{
			ant->room = lem_in->paths[0]->room;
			ft_printf("L%i-%s ", ant->ant_id, ant->room->name);
		}

*/
    /*
    while (path->next_path != NULL)
    {
        move = (t_move *)malloc(sizeof(t_move));
        move->room_name = path->room->name;
        move->next_move = NULL;
        path = path->next_path;

    }
    move = lem_in->moves;
    */
}

/**
 **		L1-1 L2-2
 **		L1-4 L2-3 L3-1
 **		L2-5 L3-4 L4-1
 **		L2-4 L4-4		
 **/