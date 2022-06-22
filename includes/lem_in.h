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

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_lem_in
{
	char		**rooms;
	char		**links;
	char		**ants;
	char		**moves;
	int			ants_count;
	int			rooms_count;
	int			links_count;
	int			moves_count;
	int			start;
	int			end;
	int			start_index;
	int			end_index;
	int			*path;
	int			*path_len;
	int			*path_index;
	int			*path_index_len;
}				t_lem_in;

typedef struct s_room
{
	char		*name;
	int			x;
	int			y;
}				t_room;

typedef struct s_link
{
	char		*name1;
	char		*name2;
}				t_link;

typedef struct s_ant
{
	int			ant_id;
	char		*room_name;
}				t_ant;

t_lem_in	*lem_in_init(void);
void		lem_in_free(t_lem_in *lem_in);
void		lem_in_add_room(t_lem_in *lem_in, char *name, int x, int y);
void		lem_in_add_link(t_lem_in *lem_in, char *name1, char *name2);
void		lem_in_add_ant(t_lem_in *lem_in, int ant_id, char *room_name);
void		lem_in_add_move(t_lem_in *lem_in, int ant_id, char *room_name);

#endif
