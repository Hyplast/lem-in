/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
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

	if (name[0] == 'L')
		handle_error(lem_in, "ERROR room name cannot begin with 'L'\n");
	if (!is_printable(name))
		handle_error(lem_in, "ERROR room name is not printable\n");
	room = (t_room *)malloc(sizeof(t_room));
	room->name = ft_strdup(name);
	room->x = x;
	room->y = y;
	room->distance = 0;
	room->visited = 0;
	room->next = lem_in->rooms;
	room->neighbors = NULL;
	room->parent = NULL;
	lem_in->rooms = room;
	lem_in->rooms_count++;
}

void	lem_in_add_link(t_lem_in *lem_in, char *name1, char *name2)
{
	t_link	*link;
	t_room	*temp_1;
	t_room	*temp_2;

	link = (t_link *)malloc(sizeof(t_link));
	temp_1 = get_room(lem_in, name1);
	temp_2 = get_room(lem_in, name2);
	if (temp_1 == NULL || temp_2 == NULL)
		handle_error(lem_in, "ERROR link not possible\n");
	if (temp_1 == temp_2)
		handle_error(lem_in, "ERROR link not possible\n");
	link->room_1 = temp_1;
	link->room_2 = temp_2;
	link->next = lem_in->links;
	lem_in->links = link;
}

void	lem_in_add_ant(t_lem_in *lem_in, int ant_id)
{
	t_ant	*ant;

	ant = (t_ant *)malloc(sizeof(t_ant));
	ant->ant_id = ant_id;
	ant->room = lem_in->start_room;
	ant->next = lem_in->ants;
	lem_in->ants = ant;
	lem_in->ants_in_start++;
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
	lem_in->paths = NULL;
	lem_in->start_room = NULL;
	lem_in->end_room = NULL;
	lem_in->start_name = NULL;
	lem_in->end_name = NULL;
	lem_in->ants_count = 0;
	lem_in->ants_in_start = 0;
	lem_in->rooms_count = 0;
	lem_in->links_count = 0;
	lem_in->moves_count = 0;
	lem_in->paths_count = 0;
	lem_in->r = 0;
	lem_in->start = 0;
	lem_in->end = 0;
	return (lem_in);
}
