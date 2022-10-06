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

void	set_visited_and_distance(t_room *room, int distance)
{
	room->visited = 1;
	room->distance = distance;
}

void	set_just_once(int *distance, int *just_once)
{
	if (*just_once == 0)
	{
		*distance++;
		*just_once = 1;
	}
}