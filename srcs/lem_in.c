/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:58:14 by severi            #+#    #+#             */
/*   Updated: 2022/06/24 00:42:22 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"

void	free_lem_in(t_lem_in *lem_in)
{
	free(lem_in->rooms);
	free(lem_in->links);
	free(lem_in->ants);
	free(lem_in->moves);
	free(lem_in);
}

int handle_error(t_lem_in *lem_in, char *error_msg)
{
	ft_putstr(error_msg);
	free_lem_in(lem_in);
	return (0);
}
	

void	print_rooms(t_lem_in *lem_in)
{
	t_room	*temp;
	int	len;

	len = 0;
	temp = lem_in->rooms;
	while (temp != NULL)
	{
		ft_printf("room_name : %10s " ,temp->name);
		ft_printf(" room_coord : %i %i\n" ,temp->x, temp->y);
		len++;
		temp = temp->next;
	}
	ft_printf("amount of rooms: %i\n" , len);
}

void	print_links(t_lem_in *lem_in)
{
	t_link	*l_temp;

	l_temp = lem_in->links;
	while (l_temp != NULL)
	{
		ft_printf("room      : %10s  linked with %10s\n" ,l_temp->name1, l_temp->name2);
		l_temp = l_temp->next;
	}
}

void	print_moves(t_lem_in *lem_in)
{
	t_move	*temp;

	temp = lem_in->moves;
	while (temp != NULL)
	{
		ft_printf("L%i-%s", temp->ant_id, temp->room_name);
		temp = temp->next;
	}
	ft_printf("\n");
}

void	do_lem_in(t_lem_in *lem_in)
{
	char	*room_start;
	char	*room_end;
	int		x;
	int		y;

	x = 23;
	y = 3;

	room_start = ft_strdup("start");
	room_end = ft_strdup("end");

	lem_in_add_room(lem_in, room_start, x, y);
	lem_in_add_room(lem_in, "middle", x, y);
	lem_in_add_room(lem_in, room_end, x, y);

	lem_in_add_link(lem_in, room_start, "middle");
	lem_in_add_link(lem_in, room_end, "middle");
	lem_in_add_link(lem_in, room_start, room_end);

	int i;
	i = 1;
	while (i++ < 10)
		lem_in_add_ant(lem_in, i, room_start);


	lem_in_add_move(lem_in, 1, room_end);
	lem_in_add_move(lem_in, 2, room_end);
	lem_in_add_move(lem_in, 3, "middle");


	print_rooms(lem_in);
	print_links(lem_in);
	print_moves(lem_in);
		// while ()
	ft_printf("room_name : %s\n" ,lem_in->rooms->name);
	ft_printf("ants : %i\n" ,lem_in->ants->ant_id);
}

void	add_to_lem_in(t_lem_in *lem_in, char *line)
{
	char	**temp;
	int		i;
	int		j;

//	while (line[i++] != ' ');
//	temp = ft_strsub(line, 0, i);
//	while (line[i+j++] != ' ');
	temp = ft_strsplit(line, ' ');
	lem_in_add_room(lem_in, temp[0], ft_atoi(temp[1]), ft_atoi(temp[2]));
	ft_strdel(temp);
	
}

int	get_lem_in(t_lem_in *lem_in)
{
	int		read;
	char	*found;
	char	*buf;
	int		i;

	read = get_next_line(0, &buf);
	if (read == 0)
	{
		perror(" ");
		exit(-1);
	}
	lem_in->ants_count = ft_atoi(buf);
	while (read != 0)
	{
		
		while (ft_isdigit(buf[i]))
			i++;
		if (i == (int)ft_strlen(buf))
			add_to_lem_in(lem_in, buf); 
		read = get_next_line(0, &buf);
	} 
	found = ft_strstr(buf, "##start");
	found = NULL;
	ft_strdel(&buf);
	found = ft_strstr(buf, "##end");
	found = NULL;
	ft_strdel(&buf);

}

int	main(int argc, char **argv)
{
	t_lem_in	*lem_in;

	if (argc != 1)
	{
		ft_printf("Usage: ./lem_in\n");
		return (0);
	}
	else if (argc == 2)
	{
		if (ft_strncmp("-v", argv[2], 2))
		{
			ft_printf("Using visualizer\n");
			return (0);
		}
	}
	lem_in = lem_in_init();
	if (!lem_in)
		return (0);
	
	get_lem_in(lem_in);
	do_lem_in(lem_in);
	free_lem_in(lem_in);
	return (0);
}
