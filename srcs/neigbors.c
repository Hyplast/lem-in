/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neigbors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	Count the amount of neigboring rooms
*	@param	Room **neighbors
*	@return	amount of neighbors
*/
size_t	ft_lstlen(t_room **neighbors)
{
	size_t		len;

	len = 0;
	if (neighbors == NULL)
		return (len);
	while (neighbors[len] != NULL)
		len++;
	return (len);
}

/*
*	Given room x, find the room y that is the shortest distance to x.
*	@return	the room that is the shortest distance to x.
*	@return NULL if no room is found. 
*/
t_room	*return_shortest_room(t_room *start, t_room *room)
{
	t_room	*temp;
	t_room	*shortest_room;
	int		shortest_distance;
	int		i;

	i = 0;
	shortest_room = NULL;
	temp = room->neighbors[i];
	shortest_distance = 2147483647;
	while (temp != NULL)
	{
		if (temp->distance < shortest_distance)
		{
			if (temp != start)
			{
				shortest_distance = temp->distance;
				shortest_room = temp;
			}
		}
		temp = room->neighbors[++i];
	}
	return (shortest_room);
}

/*
*	Add neighbors to the rooms. From shortest distance to longest.
*/
void	add_neighbors(t_room *room_1, t_room *room_2)
{
	t_room	**neighbors;
	int		i;
	size_t	len;

	i = 0;
	len = ft_lstlen(room_1->neighbors);
	neighbors = (t_room **)malloc(sizeof(t_room *) * (len + 1 + 1));
	if (len == 0)
	{
		neighbors[0] = room_2;
		neighbors[1] = NULL;
	}
	else
	{
		while (i < (int)len)
		{
			neighbors[i] = room_1->neighbors[i];
			i++;
		}
		neighbors[len] = room_2;
		neighbors[len + 1] = NULL;
	}
	free(room_1->neighbors);
	room_1->neighbors = neighbors;
}

void	swap_links_around(t_lem_in *lem_in)
{
	t_link	*temp;
	t_link	*prev;
	t_link	*new_link;
	// t_link	*link;

	temp = lem_in->links;
	prev = malloc(sizeof(t_link));
	prev->room_1 = temp->room_1;
	prev->room_2 = temp->room_2;
	temp = temp->next;
		// ft_memcpy(new_link, temp
	while (temp)
	{
		new_link = malloc(sizeof(t_link));
		new_link->room_1 = temp->room_1;
		new_link->room_2 = temp->room_2;
		prev->next = new_link;
		// if (temp->next)
			// prev = prev->next;
		// ft_memcpy(new_link, temp, sizeof(temp) * 3);
		// new_link->next = new_link;
		// if (temp)
		// 	new_link->next = temp;
		new_link->next = lem_in->links;
		lem_in->links = new_link;

		temp = temp->next;
	}
	
	lem_in->links = new_link;
	
}

/*
*	Find neighbors of the rooms. From shortest distance to longest.
*/
void	find_neighbors(t_lem_in *lem_in)
{
	t_link	*temp;

	// swap_links_around(lem_in);
	temp = lem_in->links;
	while (temp != NULL)
	{
		add_neighbors(temp->room_1, temp->room_2);
		if (temp->room_1->name[0] == 'W')
		{
			if (temp->room_1->name[1] == '_')
			{
				if (temp->room_1->name[2] == 'n')
					temp = temp->next;
				else
					temp = temp->next;
			}
			else
				temp = temp->next;
		}
		else
			temp = temp->next;
	}
}
