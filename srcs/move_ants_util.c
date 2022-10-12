/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/08/29 00:54:39 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_ant_move(int ant_id, char *room_name)
{
	ft_putchar('L');
	ft_putnbr(ant_id);
	ft_putchar('-');
	ft_putstr(room_name);
	ft_putchar(' ');
}

void	set_end(t_lem_in *lem_in, t_ant *ant)
{
	ant->room = lem_in->end_room;
	print_ant_move(ant->ant_id, ant->room->name);
	// ft_printf("L%i-%s ", ant->ant_id, ant->room->name);
}

void	check_end_and_visited(t_lem_in *lem_in, t_path *path, t_ant *ant)
{
	if (path->next_path->room == lem_in->end_room)
		set_end(lem_in, ant);
	else if (path->next_path->room->visited == 0)
	{
		ant->room = path->next_path->room;
		ant->room->visited = 1;
		print_ant_move(ant->ant_id, ant->room->name);
		// ft_printf("L%i-%s ", ant->ant_id, ant->room->name);
	}
}

int	sum_of_path_differences(t_lem_in *lem_in, t_path *path)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (lem_in->paths[i] != path)
		i++;
	while (i > 0)
		sum += path->path_length - lem_in->paths[--i]->path_length;
	return (sum);
}