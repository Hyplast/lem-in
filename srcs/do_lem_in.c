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

void	free_a_path(t_path *path)
{
	t_path	*temp;

	temp = path;
	while (temp)
	{
		path = temp;
		temp = path->next_path;
		free(path);
		path = NULL;
	}
}

void	free_a_path_from_lem_in(t_lem_in *lem_in, t_path *path)
{
	int		i;
	// t_path	*temp;

	i = 0;
	while (lem_in->paths[i] != path)
		i++;
	free_a_path(path);
	lem_in->paths[i] = NULL;

	// temp = path;
	// while( != NULL)
	// {
	// 	lem_in->paths[i] = lem_in->paths[i + 1];
	// 	i++;
	// }
	
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
*	Remove path n from lem_in
*/
void	remove_path_n(t_lem_in *lem_in, int to_be_removed)
{
	t_path	**paths;
	int		i;
	int		j;

	i = 0;
	j = 0;
	paths = init_paths(count_paths(lem_in->paths));
	while (lem_in->paths[i])
	{
		if (to_be_removed != i)
		{
			paths[j++] = lem_in->paths[i];
		}
		else
			free_a_path_from_lem_in(lem_in, lem_in->paths[i]);
		i++;
	}
	// free_a_path(paths[j]);
	paths[j] = NULL;
	free(lem_in->paths);
	lem_in->paths = paths;
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


void	do_lem_in(t_lem_in *lem_in)
{
	t_queue	*queue;
	int		i;

	i = 0;
	queue = init_queue();
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
	find_paths(lem_in);
	clock_t stop_5 = clock();
	double elapsed_3;
	elapsed_3 = (double) (stop_5 - stop_4);
	elapsed_3 = elapsed_3 * 1000.0;
	elapsed_3 = elapsed_3 / CLOCKS_PER_SEC;
	printf("find_paths elapsed in ms: %f\n", elapsed_3);
	print_paths(lem_in);
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
	bubble_sort_paths(lem_in);
	printf("Before remove duplicants\n");
	print_paths(lem_in);
	remove_duplicates(lem_in, i);
	printf("After remove duplicants\n");
	print_paths(lem_in);

	lem_in->paths_count = (int)count_paths(lem_in->paths);
	calculate_optimal_paths(lem_in);
	printf("After calculate_optimal_paths\n");
	print_paths(lem_in);
	printf("paths count:%ld\n", count_paths(lem_in->paths));
	move_ants(lem_in);
	clock_t stop_7 = clock();
	double elapsed_4 = (double)(stop_7 - stop_6) * 1000.0 / CLOCKS_PER_SEC;
	printf("find_paths elapsed in ms: %f\n", elapsed_4);
	// print_moves(lem_in);
	printf("\n");
}


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
	calculate_optimal_paths(lem_in);
	move_ants(lem_in);
	// printf("\n");
	// free_lem_in(lem_in);
}
*/
