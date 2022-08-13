/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/08/13 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    init_ants(t_lem_in *lem_in)
{
    int     ants;
    t_ant   *ant;
 
    ants = 1;
    while (lem_in->ants_count >= ants)
    {
        ant = (t_ant *)malloc(sizeof(t_ant));
        ant->ant_id = ants;
        ant->room = lem_in->start_room;
        ants++;
        ant->next = ant;
        lem_in->ants = ant;
    }
}

void    move_ants(t_lem_in *lem_in)
{
    // t_move  *move;
    // t_path  *path;
    
    init_ants(lem_in);
    
    /*
    while (path->next_path != NULL)
    {
        move = (t_move *)malloc(sizeof(t_move));
        move->room_name = path->room->name;
        move->next_move = NULL;
        path = path->next_path;

    }
    move = lem_in->moves;
    */
}