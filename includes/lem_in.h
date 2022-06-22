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
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>

typedef struct s_lem_in
{
	char		**rooms;
	char		**links;
	char		**ants;
	char		**moves;
	char		**comments;
	char		**errors;
	char		**warnings;
	char		**debugs;
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
void		lem_in_add_comment(t_lem_in *lem_in, char *comment);
void		lem_in_add_error(t_lem_in *lem_in, char *error);
void		lem_in_add_warning(t_lem_in *lem_in, char *warning);
void		lem_in_add_debug(t_lem_in *lem_in, char *debug);

#endif
