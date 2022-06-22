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

free_lem_in(lem_in)
{
    free(lem_in->rooms);
    free(lem_in->links);
    free(lem_in->ants);
    free(lem_in->moves);
    free(lem_in->comments);
    free(lem_in->errors);
    free(lem_in->warnings);
    free(lem_in->debugs);
    free(lem_in);
}

lem_in_add_room(lem_in, name, x, y)
{
    s_room *room;

    room = (s_room *)malloc(sizeof(s_room));
    room->name = name;
    room->x = x;
    room->y = y;
    room->next = lem_in->rooms;
    lem_in->rooms = room;

}

lem_in_add_link(lem_in, name1, name2)
{
    s_link *link;

    link = (s_link *)malloc(sizeof(s_link));
    link->name1 = name1;
    link->name2 = name2;
    link->next = lem_in->links;
    lem_in->links = link;

}

lem_in_add_ant(lem_in, ant_id, room_name)
{
    s_ant *ant;

    ant = (s_ant *)malloc(sizeof(s_ant));
    ant->ant_id = ant_id;
    ant->room_name = room_name;
    ant->next = lem_in->ants;
    lem_in->ants = ant;

}

lem_in_add_move(lem_in, ant_id, room_name)
{
    s_move *move;
}

t_lem_in    *lem_in_init()
{
    t_lem_in *lem_in;

    lem_in = (t_lem_in *)malloc(sizeof(t_lem_in));
    lem_in->rooms = NULL;
    lem_in->links = NULL;
    lem_in->ants = NULL;
    lem_in->moves = NULL;
    lem_in->comments = NULL;
    lem_in->errors = NULL;
    lem_in->warnings = NULL;
    lem_in->debugs = NULL;
    lem_in->ants = 0;
    lem_in->rooms = 0;
    lem_in->links = 0;
    lem_in->comments = 0;
    lem_in->errors = 0;
    lem_in->warnings = 0;
    lem_in->debugs = 0;
    lem_in->moves = 0;

    return (lem_in);
}

int main(int argc, char **argv)
{
    t_lem_in	*lem_in;
    int			i;
    int			j;
    int			k;

    lem_in = lem_in_init();

    i = 0;
    j = 0;
    k = 0;


}