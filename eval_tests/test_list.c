#include "../includes/lem_in.h"

size_t		ft_lstlen(t_room **neighbors)
{
	size_t		len;

	len = 0;
	while (neighbors[len] != NULL)
		len++;
	return (len);
}

size_t		lstlen(char **neighbors)
{
	size_t		len;

	len = 0;
    if (neighbors == NULL)
        return (len);
	while (neighbors[len] != NULL)
		len++;
	return (len);
}

void    init_room(t_room *room)
{
    room = (t_room *)malloc(sizeof(t_room));
    room->name = "room";
    room->x = 0;
    room->y = 0;
    room->distance = 0;
    room->visited = 0;
    room->next = NULL;
    room->neighbors = NULL;

}

void    add_neighbor(t_room *room_1, t_room *room_2)
{
    t_room  **neighbors;
    int i;
    size_t len;

    i = 0;
    len = ft_lstlen(room_1->neighbors);
    neighbors = (t_room **)malloc(sizeof(t_room *) * len + 1);
    if (len == 0)
        neighbors[0] = room_2;
    else
    {
        while (i < len)
        {
            neighbors[i] = room_1->neighbors[i];
            i++;
        }
    }
    neighbors[len + 1] = NULL;
    room_1->neighbors = neighbors;
}

void    add_neighbor_char(char **neighbors, char *char_1, char *char_2)
{
    char    **temp;
    int     i;
    size_t  len;

    len = lstlen(neighbors);

    temp = (char **)malloc(sizeof(char *) * len + 1);
    if (len == 0)
    {
        temp[0] = char_2;
    }
    else
    {
        while (i < len)
        {
            temp[i] = neighbors[i];
            i++;
        }
    }
    temp[len + 1] = NULL;
    neighbors = temp;
}

void    init_char(char **chars, const char *str)
{
    char    *temp;
    size_t  len;
    int     i;

    len = 0;
    while(str[len] != '\0')
        len++;
    *chars = (char *)malloc(sizeof(char) * len + 1);
    i = 0;
    while(*str != '\0')
        chars[0][i++] = *str++;
    chars[0][i] = '\0';
}

int main()
{
    t_room *room_1;
    t_room *room_2;
    t_room *room_3;
    t_room *room_4;
    t_room *room_5;
    char    *char_1;
    char    *char_2;
    char    *char_3;
    char    *char_4;
    char    *char_5;

    char_1 = malloc(sizeof(char *));
    char_2 = malloc(sizeof(char *));
    char_3 = malloc(sizeof(char *));
    char_4 = malloc(sizeof(char *));
    char_5 = malloc(sizeof(char *));

    init_char(&char_1, "room_1");
    init_char(&char_2, "room_2");
    init_char(&char_3, "room_3");
    init_char(&char_4, "room_4");
    init_char(&char_5, "room_5");

    char    **neighbors_1;

    neighbors_1 = (char **)malloc(sizeof(char *) + 1);

    add_neighbor_char(neighbors_1, char_1, char_2);
    add_neighbor_char(neighbors_1, char_1, char_3);

    init_room(room_1);
    init_room(room_2);
    init_room(room_3);
    init_room(room_4);
    init_room(room_5);



    add_neighbor(room_1, room_2);

    return 0;
}
