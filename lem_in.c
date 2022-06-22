
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
}

led_in_add_link(lem_in, name1, name2)
{
    s_link *link;
}

lem_in_add_link(lem_in, name1, name2)
{
    s_link *link;
}

lem_in_add_ant(lem_in, ant_id, room_name)
{
    s_ant *ant;
}

lem_in_add_move(lem_in, ant_id, room_name)
{
    s_move *move;
}



int main(int argc, char **argv)
{
    t_lem_in	*lem_in;
    int			i;
}