/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
*	Bread first traversal to find path lenghts between start and end rooms.
*/
void	bread_first_search(t_lem_in *lem_in, t_queue **queue, t_room *room)
{
	room->visited = 1;
	insert(queue, room);
	while (!is_queue_empty(*queue))
	{
		go_to_linked_rooms(lem_in, queue);
		queue_remove(queue);
	}
}

/*
*	Set visited rooms to zero.
*/
void	set_all_visited_to_zero(t_lem_in *lem_in)
{
	t_room	*temp;

	temp = lem_in->rooms;
	while (temp)
	{
		temp->visited = 0;
		temp = temp->next;
	}
}

/*
*	Set visited rooms in paths to zero in order to keep count which rooms are 
*	occupied by ants.
*/
void	set_visited_to_zero(t_lem_in *lem_in)
{
	t_path	*path;
	t_path	*temp;
	int		i;

	i = 0;
	path = lem_in->paths[i];
	while (path)
	{
		temp = path;
		while (temp)
		{
			temp->room->visited = 0;
			temp = temp->next_path;
		}
		path = lem_in->paths[++i];
	}
}

int		same_path(t_lem_in *lem_in, t_path *path1, t_path *path2)
{
	while (path1->room == path2->room)
	{
		path1 = path1->next_path;
		path2 = path2->next_path;
		if (path2->room == lem_in->end_room && path1->room == lem_in->end_room)
			return (1);
	}
	return (0);
}

void	remove_paths(t_lem_in *lem_in, int to_be_removed[500])
{
	t_path	**paths;
	int		num_paths;
	int		num_removed;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	num_removed = 0;
	num_paths = (int)count_paths(lem_in->paths);
	while (to_be_removed[num_removed] != -1)
		num_removed++;
	num_paths = num_paths - num_removed;
	paths = (t_path **)malloc(sizeof(t_path *) * ((size_t)num_paths + 1));
	while (lem_in->paths[i])
	{
		if (to_be_removed[k++] != i)
			paths[j++] = lem_in->paths[i];
		i++;
	}
	paths[j] = NULL;
	lem_in->paths = paths;
}

void	remove_duplicates(t_lem_in *lem_in)
{
	t_path	*path;
	// t_path	**paths;
	t_path	*temp;
	int		i;
	int		j;
	int		result;
	int		to_be_removed[500];

	i = 0;
	j = 0;
	while (i < 500)
		to_be_removed[i++] = -1;
	i = 0;
	path = lem_in->paths[i];
	while (path)
	{
		temp = lem_in->paths[i + 1];
		while (temp)
		{
			if (path->path_length == temp->path_length)
			{
				result = same_path(lem_in, path, temp);
				if (result == 1)
					to_be_removed[j++] = i;
			}
			temp = temp->next_path;
		}
		path = lem_in->paths[++i];
	}
	remove_paths(lem_in, to_be_removed);
}

void	do_lem_in(t_lem_in *lem_in)
{
	t_queue	*queue;

	queue = init_queue();
	// print_rooms(lem_in);
	// print_links(lem_in);
	// print_ants(lem_in);
	// ft_printf("room_name : %s\n", lem_in->rooms->name);
	// ft_printf("ants : %i\n", lem_in->ants->ant_id);
	// ft_printf("nextl line\n");
	clock_t stop_2 = clock();
	bread_first_search(lem_in, &queue, lem_in->start_room);
	clock_t stop_3 = clock();
	double elapsed = (double)(stop_3 - stop_2) * 1000.0 / CLOCKS_PER_SEC;
    printf("bread_first_search elapsed in ms: %f\n", elapsed);
	// free(queue);
	find_neighbors(lem_in);
	clock_t stop_4 = clock();
	double elapsed_2 = (double)(stop_4 - stop_3) * 1000.0 / CLOCKS_PER_SEC;
    printf("find_neighbors elapsed in ms: %f\n", elapsed_2);
	// ft_printf("\n $£€\n");
	// ft_printf(lem_in->rooms->name);
	// ft_printf("\n");
	// print_rooms(lem_in);
	// ft_printf("START ROOM as t_room->name: %s \n", lem_in->start_room->name);
	// ft_printf("END ROOM as t_room->name: %s \n", lem_in->end_room->name);
	// print_neighbors(lem_in->rooms);
	// print_neighbors(lem_in->rooms->next);
	// print_neighbors(lem_in->rooms->next->next);
	// print_neighbors(lem_in->rooms->next->next->next);
	// print_neighbors(lem_in->rooms->next->next->next->next);
	find_paths(lem_in);
	clock_t stop_5 = clock();
	double elapsed_3;
	elapsed_3 = (double) (stop_5 - stop_4);
	elapsed_3 = elapsed_3 * 1000.0;
	elapsed_3 = elapsed_3 / CLOCKS_PER_SEC;
    printf("find_paths elapsed in ms: %f\n", elapsed_3);
	// ft_printf(queue->room->name);
	print_paths(lem_in);
	set_all_visited_to_zero(lem_in);
	queue = init_queue();
	bread_first_search(lem_in, &queue, lem_in->end_room);
	find_paths_reverse_order(lem_in);
	print_paths(lem_in);
	change_paths_order(lem_in);

	set_visited_to_zero(lem_in);
	print_paths(lem_in);
	clock_t stop_6 = clock();
	bubble_sort_paths(lem_in);
	print_paths(lem_in);
	printf("Before remove duplicants\n");
	remove_duplicates(lem_in);
	printf("After remove duplicants\n");
	print_paths(lem_in);
	calculate_optimal_paths(lem_in);
	print_paths(lem_in);
	move_ants(lem_in);
	clock_t stop_7 = clock();
	double elapsed_4 = (double)(stop_7 - stop_6) * 1000.0 / CLOCKS_PER_SEC;
    printf("find_paths elapsed in ms: %f\n", elapsed_4);
	// print_moves(lem_in);
	printf("\n");
}
