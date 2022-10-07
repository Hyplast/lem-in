/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/28 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h> // REMOVE !!
# include <time.h>	// REMOVE !!
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_queue
{
	struct s_room	*room;
	int				queue_item_count;
	struct s_queue	*next;
}					t_queue;

typedef struct s_room
{
	char			*name;
	int				x;
	int				y;
	int				distance;
	int				visited;
	struct s_room	*next;
	struct s_room	**neighbors;
}					t_room;

typedef struct s_link
{
	struct s_room	*room_1;
	struct s_room	*room_2;
	struct s_link	*next;
}					t_link;

typedef struct s_ant
{
	int				ant_id;
	struct s_room	*room;
	struct s_ant	*next;
}					t_ant;

typedef struct s_move
{
	int				ant_id;
	char			*room_name;
	struct s_move	*next;
}					t_move;

typedef struct s_path
{
	struct s_path	*next_path;
	int				path_length;
	struct s_room	*room;
}					t_path;

typedef struct s_lem_in
{
	t_room		*rooms;
	t_link		*links;
	t_ant		*ants;
	t_move		*moves;
	t_path		**paths;
	int			ants_count;
	int			ants_in_start;
	int			rooms_count;
	int			links_count;
	int			moves_count;
	int			paths_count;
	int			start;
	int			end;
	t_room		*start_room;
	t_room		*end_room;
	char		*start_name;
	char		*end_name;
}				t_lem_in;

t_lem_in	*lem_in_init(void);
void		free_lem_in(t_lem_in *lem_in);
void		lem_in_add_room(t_lem_in *lem_in, char *name, int x, int y);
void		lem_in_add_link(t_lem_in *lem_in, char *name1, char *name2);
void		lem_in_add_ant(t_lem_in *lem_in, int ant_id);
void		lem_in_add_move(t_lem_in *lem_in, int ant_id, char *room_name);
int			is_number(char *str);
int			is_printable(char *str);
t_room		*get_room(t_lem_in *lem_in, char *room_name);
void		check_lem_in(t_lem_in *lem_in);
int			lenght_of_array(char **array);
size_t		ft_lstlen(t_room **neighbors);
void		do_lem_in(t_lem_in *lem_in);
void		print_rooms(t_lem_in *lem_in);
void		print_links(t_lem_in *lem_in);
void		print_moves(t_lem_in *lem_in);
void		print_ants(t_lem_in *lem_in);
void		print_paths(t_lem_in *lem_in);
int			handle_error(t_lem_in *lem_in, char *error_msg);
t_queue		*init_queue(void);
void		insert(t_queue **queue, t_room *room);
void		queue_remove(t_queue **queue);
int			is_queue_empty(t_queue *queue);
void		go_to_linked_rooms(t_lem_in *lem_in, t_queue **queue, t_room *room);
void		lem_in_add_to_path(t_path **path, t_room *room);
t_path		*lem_in_add_new_path(t_room *room);
void		find_paths(t_lem_in *lem_in);
void		find_paths_reverse_order(t_lem_in *lem_in);
void		change_paths_order(t_lem_in *lem_in);
void		fd_sho_path(t_lem_in *lem_in, t_room *room, t_room *start, t_room *end);
void		free_paths(t_lem_in *lem_in);
void		move_ants(t_lem_in *lem_in);
void		set_end(t_lem_in *lem_in, t_ant *ant);
void		set_visited_to_zero(t_lem_in *lem_in);
void		set_all_visited_to_zero(t_lem_in *lem_in);
void		check_end_and_visited(t_lem_in *lem_in, t_path *path, t_ant *ant);
void		add_neighbors(t_room *room_1, t_room *room_2);
void		find_neighbors(t_lem_in *lem_in);
t_room		*return_shortest_room(t_room *start, t_room *room);
void		calculate_optimal_paths(t_lem_in *lem_in);
void		bubble_sort_paths(t_lem_in *lem_in);
int			is_path_unique(t_lem_in *lem_in, t_path *path_1, t_path *path_2);
int			check_all_paths_uniq(t_lem_in *lem_in, t_path *path_1, t_path **paths);
int			min_number(int x, int replace[100]);
int			calculate_neigbors(t_lem_in *lem_in);
size_t		count_paths(t_path **paths);
t_path		**create_paths(t_lem_in *lem_in, size_t	size);
t_path		*get_shortest_path(t_lem_in *lem_in);
void		bread_first_search(t_lem_in *lem_in, t_queue **queue, t_room *room);
void		check_for_max_neigbor_option(t_lem_in *lem_in, t_path **paths, int max_neigbors);
void		check_for_goal(t_lem_in *lem_in, t_link *temp, t_room *room);
int			find_permuntations(t_lem_in *lem_in, t_path **paths, int size);
void		remove_ant_from_lem_in(t_lem_in *lem_in, t_ant *ant);
void		remove_ants_in_goal(t_lem_in *lem_in);
int			remove_last_path(t_lem_in *lem_in, t_path **paths);
float		calculate_path_turns(t_lem_in *lem_in, t_path **paths);
void		add_path_to_paths(t_path **paths, t_path *path);
int			remove_path_from_paths(t_lem_in *lem_in, t_path **paths);

#endif
