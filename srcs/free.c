/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
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
	free(lem_in->paths);
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
		ft_strdel(&room->name);
		free(room->neighbors);
		room->neighbors = NULL;
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
	ft_strdel(&lem_in->start_name);
	ft_strdel(&lem_in->end_name);
	free(lem_in);
	lem_in = NULL;
}
