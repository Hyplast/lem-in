/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
