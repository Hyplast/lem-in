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

int	same_path(t_lem_in *lem_in, t_path *path1, t_path *path2)
{
	if (path1 == path2)
		return (0);
	while (path1->room == path2->room)
	{
		path1 = path1->next_path;
		path2 = path2->next_path;
		if (path2->room == lem_in->end_room && path1->room == lem_in->end_room)
			return (1);
	}
	return (0);
}

t_path	**init_paths(size_t size)
{
	t_path	**paths;
	size_t	i;

	i = 0;
	paths = (t_path **)malloc(sizeof(t_path *) * (size + 1));
	while (i <= size)
		paths[i++] = NULL;
	return (paths);
}

/*
*	Remove any duplicate paths from paths list.
*/
void	remove_duplicates(t_lem_in *lem_in, int i)
{
	t_path	*path;
	t_path	*temp;
	int		result;
	int		j;

	j = 0;
	path = lem_in->paths[i];
	while (path)
	{
		temp = lem_in->paths[0];
		while (temp)
		{
			result = same_path(lem_in, path, temp);
			if (result == 1)
			{
				remove_path_n(lem_in, j);
				j = -1;
				i = 0;
			}
			temp = lem_in->paths[++j];
		}
		j = 0;
		path = lem_in->paths[++i];
	}
}

void	print_paths(t_lem_in *lem_in)
{
	t_path	*temp;
	t_path	*path;
	int		i;

	i = 0;
	temp = lem_in->paths[i++];
	while (temp != NULL)
	{
		path = temp;
		while (path != NULL)
		{
			ft_printf("%s ->", path->room->name);
			path = path->next_path;
		}
		ft_printf("path_length : %i\n", temp->path_length);
		temp = lem_in->paths[i++];
	}
	ft_printf("\n");
}


/*
*	Fix starting path to lem_in->start and ending path to lem_in->end.
*/
void	change_paths_order_i(t_lem_in *lem_in, int i)
{
	t_path	*path;

	path = lem_in->paths[i];
	while (path)
	{
		if (path->room == lem_in->start_room)
			start_to_end(lem_in, &path);
		else if (path->room == lem_in->end_room)
			end_to_start(lem_in, path);
		path = lem_in->paths[++i];
	}
}


/*
*	Ant solver
*/
void	do_lem_in(t_lem_in *lem_in)
{
	t_queue	*queue;
	int		i;
	int	max_paths;

	
	i = 0;
	queue = init_queue();
	// swap_links_around(lem_in);
	find_neighbors(lem_in);

	bread_first_search(lem_in, &queue, lem_in->start_room);
	
	
	max_paths = calculate_neigbors(lem_in);

	// print_rooms(lem_in);
	// print_paths(lem_in);
	set_all_zero_dist_to_max(lem_in);

	find_the_shortest_path(lem_in);

	// print_rooms(lem_in);
	// print_paths(lem_in);

	change_paths_order(lem_in);
	remove_duplicates(lem_in, i);

	

	// print_rooms(lem_in);
	// print_paths(lem_in);

	set_all_visited_to_zero(lem_in);


	if (lem_in->ants_count != 1 && max_paths != 1)
	{
		recalculate_bfs(lem_in, max_paths);
		// print_paths(lem_in);
		edmonkarp(lem_in, max_paths);
	

	// print_rooms(lem_in);
	// print_paths(lem_in);

	// find_paths(lem_in);
	// print_paths(lem_in);

	set_all_visited_to_zero(lem_in);
	
	// recalculate_bfs(lem_in, lem_in->start_room);
	// print_rooms(lem_in);
	// print_paths(lem_in);

	// set_all_visited_to_zero(lem_in);

	// queue = init_queue();
	// bread_first_search(lem_in, &queue, lem_in->end_room);
	// print_rooms(lem_in);
	// set_all_visited_to_zero(lem_in);

	// print_rooms(lem_in);
	// find_paths_reverse_order(lem_in);
	// change_paths_order(lem_in);
	// set_visited_to_zero(lem_in);
	// bubble_sort_paths(lem_in);
	// remove_duplicates(lem_in, i);

	// print_paths(lem_in);
	// edmonkarp(lem_in);

	
	lem_in->paths_count = (int)count_paths(lem_in->paths);
	// ft_printf("after edmonkarp\n");
	// print_paths(lem_in);

	// set_visited_to_zero(lem_in);


	set_all_visited_to_zero(lem_in);

	queue = init_queue();
	bread_first_search(lem_in, &queue, lem_in->start_room);
	find_paths(lem_in);

	set_all_visited_to_zero(lem_in);
	queue = init_queue();
	bread_first_search(lem_in, &queue, lem_in->end_room);
	find_paths_reverse_order(lem_in);

	change_paths_order_i(lem_in, lem_in->paths_count);

	set_visited_to_zero(lem_in);
	bubble_sort_paths(lem_in);
	remove_duplicates(lem_in, i);
	// more_paths(lem_in);
	set_visited_to_zero(lem_in);
	
	// print_paths(lem_in);

	calculate_optimal_paths(lem_in);
	// ft_printf("after calculate_optimal_paths\n");
	// print_paths(lem_in);

	}
	set_visited_to_zero(lem_in);

	move_ants(lem_in);
}
