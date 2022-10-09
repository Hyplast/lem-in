/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lem_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	Check if the matching char *room name exists in the array of rooms
*	@returns the pointer of the room if it exists, otherwise returns NULL
*/
t_room	*get_room(t_lem_in *lem_in, char *room_name)
{
	t_room	*temp;

	temp = lem_in->rooms;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, room_name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/*
*	Check if string is printable
*/
int	is_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isprint(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_lem_in(t_lem_in *lem_in)
{	
	t_room	*start;
	t_room	*end;
	int		i;

	i = 0;
	if (lem_in->start_name == NULL)
		handle_error(lem_in, "start room not found\n");
	start = get_room(lem_in, lem_in->start_name);
	if (start == NULL)
		handle_error(lem_in, "start room not found\n");
	lem_in->start_room = start;
	if (lem_in->end_name == NULL)
		handle_error(lem_in, "end room not found\n");
	end = get_room(lem_in, lem_in->end_name);
	if (end == NULL)
		handle_error(lem_in, "end room not found\n");
	lem_in->end_room = end;
	while (i++ < lem_in->ants_count)
		lem_in_add_ant(lem_in, lem_in->ants_count - i + 1);
}
