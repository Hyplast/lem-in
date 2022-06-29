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

# include <stdio.h>
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
	struct s_room	*room;
	struct s_path	*next;
}					t_path;

typedef struct s_lem_in
{
	t_room		*rooms;
	t_link		*links;
	t_ant		*ants;
	t_move		*moves;
	t_path		*paths;
	int			ants_count;
	int			rooms_count;
	int			links_count;
	int			moves_count;
	int			start;
	int			end;
	t_room		*start_room;
	t_room		*end_room;
	char		*start_name;
	char		*end_name;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	int			start_index;
	int			end_index;
	int			*path;
	int			*path_len;
	int			*path_index;
	int			*path_index_len;
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
void		do_lem_in(t_lem_in *lem_in);
void		print_rooms(t_lem_in *lem_in);
void		print_links(t_lem_in *lem_in);
void		print_moves(t_lem_in *lem_in);
void		print_ants(t_lem_in *lem_in);
int			handle_error(t_lem_in *lem_in, char *error_msg);
t_queue		*init_queue(void);
void		insert(t_queue **queue, t_room *room);
void		queue_remove(t_queue **queue);
int			is_queue_empty(t_queue *queue);
void		lem_in_add_path(t_lem_in *lem_in, t_room *room);

#endif
