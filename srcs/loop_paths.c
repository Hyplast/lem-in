/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*   Inorder to take into account path superpositions, try to find paths
*   different from previous paths by looking for paths running throught
*   different rooms. First set each room that has a path running throught it
*   to visited except start and end neighbors.
*/
void	loop_paths(t_lem_in *lem_in)
{
	int		i;
	int		j;
	t_room	*room;
	t_queue	*queue;

	i = 0;
	j = 0;
	while(i < lem_in->paths_count)
	{
		queue = init_queue();
		set_all_visited_to_zero(lem_in);
		set_one_path_to_visited(lem_in, lem_in->paths[i]);
		bread_first_search(lem_in, &queue, lem_in->end_room);
		set_all_visited_to_zero(lem_in);
		set_one_path_to_visited(lem_in, lem_in->paths[i]);
		room = lem_in->start_room->neighbors[j];
		lem_in->start_room->distance = 2147483647;
		while(room)
		{
			if (room != lem_in->paths[i]->room)
			{
				check_path_non_occupied(lem_in, room, lem_in->start_room,
					lem_in->end_room);
			}
			room = lem_in->start_room->neighbors[++j];
		}
		j = 0;
		i++;
	}
	// print_paths(lem_in);
	change_paths_order_reverse(lem_in);
	lem_in->paths_count = (int)count_paths(lem_in->paths);
}

