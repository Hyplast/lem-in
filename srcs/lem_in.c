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


// /*
// *	Bread first traversal to find the shortest path
// */
// void	bfs_algorithm(t_lem_in *lem_in)
// {
// 	lem_in->start_room->visited = 1;
// 	lem_in->start_room->distance = 0;
// 	lem_in->start_room->parent = NULL;
// 	lem_in->queue = lem_in->start_room;

// }



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
	t_link	*temp;

	temp = lem_in->links;
	while (temp != NULL)
	{
		ft_printf("room      : %10s  linked with %10s\n" , temp->name1, temp->name2);
		temp = temp->next;
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

void	print_ants(t_lem_in *lem_in)
{
	t_ant	*temp;

	temp = lem_in->ants;
	while (temp != NULL)
	{
		ft_printf("ant_id : %i room_name : %s\n" , temp->ant_id, temp->room_name);
		temp = temp->next;
	}
}

/*
*	Calculate lenght of the string array
*/
int		lenght_of_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}


/*
*	Add ants to the start room
*/

void	add_to_lem_in(t_lem_in *lem_in, char *line)
{
	char	**temp;

	temp = ft_strsplit(line, ' ');
	if (lenght_of_array(temp) == 3)
		lem_in_add_room(lem_in, ft_strdup(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2]));
	ft_free_array(temp);
	temp = ft_strsplit(line, '-');
	if (lenght_of_array(temp) == 2)
	{
		lem_in_add_link(lem_in, ft_strdup(temp[0]), ft_strdup(temp[1]));
		lem_in_add_link(lem_in, ft_strdup(temp[1]), ft_strdup(temp[0]));
	}
	ft_free_array(temp);
}




/* Reverse the order of the elements in the array 
*  of void * pointers.
*  The array must be terminated by a NULL pointer.
*/
void	reverse_array(void **array)
{
	void	*temp;
	int		i;

	i = 0;
	while (array[i] != NULL)
	{
		temp = array[i];
		array[i] = array[i + 1];
		array[i + 1] = temp;
		i++;
	}
}


/*
*	If equals ##start or ##end handle it
*/
void	handle_start_end(t_lem_in *lem_in, char *line)
{
	size_t	i;

	i = 0;
	if (ft_strcmp(line, "##start") == 0)
	{
		lem_in->start = 1;
		return ;
	}
	if (ft_strcmp(line, "##end") == 0)
	{
		lem_in->end = 1;
		return ;
	}
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (lem_in->start == 1)
		lem_in->start_room = ft_strsub(line, 0, i);
	else if (lem_in->end == 1)
		lem_in->end_room = ft_strsub(line, 0, i);
	lem_in->start = 0;
	lem_in->end = 0;
}

/*
*	Check if string is a number
*/
int		is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}


/*
*	Read the lem-in file and create a t_lem_in structure.
*/
void	get_lem_in(t_lem_in *lem_in)
{
	int		read;
	char	*buf;
	int		i;

	i = 0;
	read = get_next_line(0, &buf);
	if (read == 0 || read == -1 || buf == NULL)
	{
		perror(" ");
		exit(-1);
	}
	if (is_number(buf) == 1)
		lem_in->ants_count = ft_atoi(buf);
	else
		exit(-1);
	read = get_next_line(0, &buf);
	while (read != 0 && ft_strcmp("", buf) != 0)
	{
		handle_start_end(lem_in, buf);
		add_to_lem_in(lem_in, buf); 
		read = get_next_line(0, &buf);
	} 
	ft_strdel(&buf);
	while (i++ < lem_in->ants_count)
		lem_in_add_ant(lem_in, i, lem_in->start_room);
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
