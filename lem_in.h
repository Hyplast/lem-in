# ifndef LEM_IN_H
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

s_struct *lem_in;
{
    t_lem_in	*lem_in;
    int			i;
    int			j;
    int			k;
    int			l;
    int			m;
    int			n;
    int			o;
    int			p;
    int			q;
    int			r;
    int			s;
    int			t;
    int			u;
    int			v;
    int			w;
    int			x;
    int			y;
    int			z;
    int			aa;
    int			bb;
}   t_struct    *lem_in;


s_stuct_lem_in	*lem_in_init(void);
void			lem_in_free(s_stuct_lem_in *lem_in);
void			lem_in_add_room(s_stuct_lem_in *lem_in, char *name, int x, int y);
void			lem_in_add_link(s_stuct_lem_in *lem_in, char *name1, char *name2);
void			lem_in_add_ant(s_stuct_lem_in *lem_in, int ant_id, char *room_name);
void			lem_in_add_move(s_stuct_lem_in *lem_in, int ant_id, char *room_name);
void			lem_in_add_comment(s_stuct_lem_in *lem_in, char *comment);
void			lem_in_add_error(s_stuct_lem_in *lem_in, char *error);
void			lem_in_add_warning(s_stuct_lem_in *lem_in, char *warning);
void			lem_in_add_debug(s_stuct_lem_in *lem_in, char *debug);


#endif /* LEM_IN_H */
