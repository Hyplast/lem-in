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

void	init_ants(t_lem_in *lem_in)
{
	int	ants;

	ants = 1;
	while (lem_in->ants_count >= ants)
	{
		lem_in_add_ant(lem_in, ants);
		ants++;
	}
}

/*
*	Calculate lenght of the string array
*/
int	lenght_of_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

/*
*   Check if string is a number
*/
int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/*
*	Get the minium number from last position before -1 
*	and add +1 to it to make sure the same path is not counted
*	again.
*/
int	min_number(int x, int replace[100])
{
	int	i;

	i = 0;
	if (replace[i] == -1)
		return (0);
	while (replace[i] != -1)
		i++;
	if (x - 1 == replace[i - 1])
		return (replace[i - 1]);
	return (replace[i - 1] + 1);
}

/*
*	Check if linked room is the goal, if it is, set it's distance to max
*	int for preventing the exploring algorithm taking illegal shortcuts 
*	through rooms.
*/
void	check_for_goal(t_lem_in *lem_in, t_link *temp, t_room *room)
{
	if (temp->room_2 == lem_in->end_room
		|| temp->room_2 == lem_in->start_room)
	{
		if (temp->room_2 != room)
		{
			temp->room_2->visited = 1;
			temp->room_2->distance = 2147483647;
		}
	}
}
