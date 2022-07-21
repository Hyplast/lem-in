/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lem_in_add_path(t_lem_in *lem_in, t_room *room)
{
	t_path	*path;

	path = (t_path *)malloc(sizeof(t_path));
	path->room = room;
	path->next = lem_in->paths;
	lem_in->paths = path;
}

// 10 ants -> 10 paths -> 1 turn
// distance 1 -< turn , distance 2 - 
// in the same amount of time distance 4 will take 9 turns to disport 5 ants
// distance 7 will take 7 turns and have transported 5/7*5 = 
// 10 ants -> 5 paths -> 2 turns
// 10 ants -> 4 paths -> 3 turns

// distance + ants - 1 = turns

// 10 ants
// 3 paths

// 10 ants * distance 4 = 13 turns
// max (9_ants*dist_4, 1_ants*dist_5) = 12 turns
// max (8_ants*dist_4, 2_ants*dist_5) = 11 turns
// max (7_ants*dist_4, 3_ants*dist_5) = 10 turns
// max (6_ants*dist_4, 4_ants*dist_5) = 9 turns
// max (5_ants*dist_4, 5_ants*dist_5) = 9 turns
// max (4_ants*dist_4, 6_ants*dist_5) = 10 turns

//max (9_ants*dist_4, 1_ants*dist_5, 0_ants*dist_6) = 12 turns
//max (8_ants*dist_4, 2_ants*dist_5, 0_ants*dist_6) = 11 turns
//max (7_ants*dist_4, 3_ants*dist_5, 0_ants*dist_6) = 10 turns
//max (6_ants*dist_4, 4_ants*dist_5, 0_ants*dist_6) = 9 turns
//max (5_ants*dist_4, 5_ants*dist_5, 0_ants*dist_6) = 9 turns
//max (4_ants*dist_4, 6_ants*dist_5, 0_ants*dist_6) = 10 turns
//max (8_ants*dist_4, 1_ants*dist_5, 1_ants*dist_6) = 11 turns
//max (7_ants*dist_4, 2_ants*dist_5, 1_ants*dist_6) = 10 turns
//max (7_ants*dist_4, 2_ants*dist_5, 2_ants*dist_6) = 10 turns
//max (6_ants*dist_4, 3_ants*dist_5, 1_ants*dist_6) = 9 turns
//max (6_ants*dist_4, 3_ants*dist_5, 2_ants*dist_6) = 9 turns
//max (5_ants*dist_4, 3_ants*dist_5, 2_ants*dist_6) = 8 turns
//max (5_ants*dist_4, 4_ants*dist_5, 1_ants*dist_6) = 8 turns
//max (4_ants*dist_4, 3_ants*dist_5, 3_ants*dist_6) = 8 turns

//max (4_ants*dist_4, 3_ants*dist_5, 2_ants*dist_6, 1_ants*dist7) = 7 turns
//max (4_ants*dist_4, 4_ants*dist_4, 1_ants*dist_5, 0_ants*dist7) = 7 turns



