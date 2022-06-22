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

#include lem_in.h

void	free_lem_in(t_lem_in *lem_in)
{
	free(lem_in->rooms);
	free(lem_in->links);
	free(lem_in->ants);
	free(lem_in->moves);
	free(lem_in);
}

void	lem_in_add_room(t_lem_in *lem_in, char *name, int x, int y)
{
	t_room	*room;

	room = (s_room *)malloc(sizeof(s_room));
	room->name = name;
	room->x = x;
	room->y = y;
	room->next = lem_in->rooms;
	lem_in->rooms = room;
}

void	lem_in_add_link(t_lem_in *lem_in, char *name1, char *name2)
{
	t_link	*link;

	link = (t_link *)malloc(sizeof(s_link));
	link->name1 = name1;
	link->name2 = name2;
	link->next = lem_in->links;
	lem_in->links = link;
}

void	lem_in_add_ant(t_lem_in *lem_in, int ant_id, char *room_name)
{
	s_ant	*ant;

	ant = (t_ant *)malloc(sizeof(s_ant));
	ant->ant_id = ant_id;
	ant->room_name = room_name;
	ant->next = lem_in->ants;
	lem_in->ants = ant;
}

void	lem_in_add_move(t_lem_in *lem_in, int ant_id, char *room_name)
{
	s_move	*move;

	move = (t_move *)malloc(sizeof(s_move));
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
	return (lem_in);
}

int	main(int argc, char **argv)
{
	t_lem_in	*lem_in;
	int			i;
	int			j;
	int			k;

	lem_in = lem_in_init();
	i = 0;
	j = 0;
	k = 0;
	return (0);
}
