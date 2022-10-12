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

/*
void	do_lem_in(t_lem_in *lem_in)
{
	t_queue	*queue;
	int		i;

	i = 0;
	queue = init_queue();
	clock_t stop_2 = clock();
	bread_first_search(lem_in, &queue, lem_in->start_room);

	// free(queue);
	find_neighbors(lem_in);
	
	
	find_paths(lem_in);
	// 
	// double elapsed_3;
	// elapsed_3 = (double) (stop_5 - stop_4);
	// elapsed_3 = elapsed_3 * 1000.0;
	// elapsed_3 = elapsed_3 / CLOCKS_PER_SEC;
	
	print_paths(lem_in);

	clock_t stop_3 = clock();
	

	set_all_visited_to_zero(lem_in);
	queue = init_queue();
	bread_first_search(lem_in, &queue, lem_in->end_room);
	printf("bfs after before reverse order\n");
	print_paths(lem_in);
	find_paths_reverse_order(lem_in);
	print_paths(lem_in);
	change_paths_order(lem_in);
	set_visited_to_zero(lem_in);
	print_paths(lem_in);
	clock_t stop_6 = clock();
	double elapsed = (double)(stop_6 - stop_3) * 1000.0 / CLOCKS_PER_SEC;

	bubble_sort_paths(lem_in);
	printf("Before remove duplicants\n");
	print_paths(lem_in);
	remove_duplicates(lem_in, i);
	printf("After remove duplicants\n");
	print_paths(lem_in);

	lem_in->paths_count = (int)count_paths(lem_in->paths);

	clock_t stop_4 = clock();
	double elapsed_2 = (double)(stop_4 - stop_6) * 1000.0 / CLOCKS_PER_SEC;

	calculate_optimal_paths(lem_in);
	printf("After calculate_optimal_paths\n");
	print_paths(lem_in);
	printf("paths count:%ld\n", count_paths(lem_in->paths));
	move_ants(lem_in);
	clock_t stop_7 = clock();
	double elapsed_4 = (double)(stop_7 - stop_4) * 1000.0 / CLOCKS_PER_SEC;
	printf(" first part elapsed in ms: %53f\n", elapsed);
	printf("bubble-sort,  remove-duplicateselapsed in ms: %46f\n", elapsed_2);
	// printf("find_paths elapsed in ms: %f\n", elapsed_3);

	printf("calculate-optimal and move-ants  elapsed in ms: %46f\n", elapsed_4);
	// print_moves(lem_in);
	clock_t stop_5 = clock();
	double elapsed_22 = (double)(stop_5 - stop_2) * 1000.0 / CLOCKS_PER_SEC;
	printf("Total do lem in elapsed in ms: %56f\n", elapsed_22);
	printf("starting room neighbors: %15d\n", calculate_neigbors(lem_in));
	printf("\n");
}
*/

/*
*	Ant solver
*//*
void	do_lem_in(t_lem_in *lem_in)
{
	t_queue	*queue;
	int		i;

	i = 0;
	queue = init_queue();
	bread_first_search(lem_in, &queue, lem_in->start_room);
	find_neighbors(lem_in);
	find_paths(lem_in);
	set_all_visited_to_zero(lem_in);
	queue = init_queue();
	bread_first_search(lem_in, &queue, lem_in->end_room);
	find_paths_reverse_order(lem_in);
	change_paths_order(lem_in);
	set_visited_to_zero(lem_in);
	bubble_sort_paths(lem_in);
	remove_duplicates(lem_in, i);
	lem_in->paths_count = (int)count_paths(lem_in->paths);
	clock_t stop_1 = clock();
	calculate_optimal_paths(lem_in);
	clock_t stop_2 = clock();
	move_ants(lem_in);
	clock_t stop_3 = clock();
	double elapsed_1 = (double)(stop_2 - stop_1) * 1000.0 / CLOCKS_PER_SEC;
	double elapsed_2 = (double)(stop_3 - stop_2) * 1000.0 / CLOCKS_PER_SEC;
	printf("\nCalculate optimal ants elapsed in ms: %26f\n", elapsed_1);
	printf("Move ants elapsed in ms:              %26f\n", elapsed_2);
}
*/

/*
*	Ant solver
*/
void	do_lem_in(t_lem_in *lem_in)
{
	t_queue	*queue;
	int		i;

	i = 0;
	queue = init_queue();
	bread_first_search(lem_in, &queue, lem_in->start_room);
	find_neighbors(lem_in);
	find_paths(lem_in);
	set_all_visited_to_zero(lem_in);
	queue = init_queue();
	bread_first_search(lem_in, &queue, lem_in->end_room);
	find_paths_reverse_order(lem_in);
	change_paths_order(lem_in);
	set_visited_to_zero(lem_in);
	bubble_sort_paths(lem_in);
	remove_duplicates(lem_in, i);
	lem_in->paths_count = (int)count_paths(lem_in->paths);
	calculate_optimal_paths(lem_in);
	move_ants(lem_in);
}
