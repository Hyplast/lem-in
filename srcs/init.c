/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lem_in_add_room(t_lem_in *lem_in, char *name, int x, int y)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	room->name = name;
	room->x = x;
	room->y = y;
	room->next = lem_in->rooms;
	lem_in->rooms = room;
}

void	lem_in_add_link(t_lem_in *lem_in, char *name1, char *name2)
{
	t_link	*link;

	link = (t_link *)malloc(sizeof(t_link));
	link->name1 = name1;
	link->name2 = name2;
	link->next = lem_in->links;
	lem_in->links = link;
}

void	lem_in_add_ant(t_lem_in *lem_in, int ant_id, char *room_name)
{
	t_ant	*ant;

	ant = (t_ant *)malloc(sizeof(t_ant));
	ant->ant_id = ant_id;
	ant->room_name = room_name;
	ant->next = lem_in->ants;
	lem_in->ants = ant;
}

void	lem_in_add_move(t_lem_in *lem_in, int ant_id, char *room_name)
{
	t_move	*move;

	move = (t_move *)malloc(sizeof(t_move));
	move->ant_id = ant_id;
	move->room_name = room_name;
	move->next = lem_in->moves;
	lem_in->moves = move;
}

t_lem_in	*lem_in_init(void)
{
	t_lem_in	*lem_in;

	lem_in = (t_lem_in *)malloc(sizeof(t_lem_in));
	lem_in->rooms = NULL;
	lem_in->links = NULL;
	lem_in->ants = NULL;
	lem_in->moves = NULL;
	lem_in->ants_count = 0;
	lem_in->rooms_count = 0;
	lem_in->links_count = 0;
	lem_in->moves_count = 0;
	lem_in->start = 0;
	lem_in->end = 0;
	return (lem_in);
}
