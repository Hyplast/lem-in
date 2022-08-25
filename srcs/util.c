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

void	free_paths(t_lem_in *lem_in)
{
	t_path	*path;
	t_path	*paths;
	t_path	*temp;
	int		i;

	i = 0;
	paths = lem_in->paths[i];
	while (paths)
	{
		path = paths->next_path;
		while (path)
		{
			temp = path->next_path;
			free(path);
			path = temp;
		}
		free(paths);
		paths = lem_in->paths[++i];
	}
	lem_in->paths = NULL;
}

void	free_rooms(t_lem_in *lem_in)
{
	t_room	*room;
	t_room	*temp;

	room = lem_in->rooms;
	while (room)
	{
		temp = room->next;
		free(room);
		room = temp;
	}
	lem_in->rooms = NULL;
}

void	free_links(t_lem_in *lem_in)
{
	t_link	*link;
	t_link	*temp;

	link = lem_in->links;
	while (link)
	{
		temp = link->next;
		free(link);
		link = temp;
	}
	lem_in->links = NULL;
}

void	free_ants(t_lem_in *lem_in)
{
	t_ant	*ant;
	t_ant	*temp;

	ant = lem_in->ants;
	while (ant)
	{
		temp = ant->next;
		free(ant);
		ant = temp;
	}
	lem_in->ants = NULL;
}

void	free_lem_in(t_lem_in *lem_in)
{
	free_links(lem_in);
	free_ants(lem_in);
	free_paths(lem_in);
	free_rooms(lem_in);
	free(lem_in);
	lem_in = NULL;
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

