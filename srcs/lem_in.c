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

/*
*	Check if string is digits
*/
int	is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_for_integer(char *str)
{
	int	i;

	i =	is_digits(str);
	if (i == 1)
		return (ft_atoi(str));
	ft_putstr("error coordinates are not digits\n");
	exit(1);
}

/*
*	Add rooms and links to the lem_in struct
*/
void	add_to_lem_in(t_lem_in *lem_in, char *line)
{
	char	**temp;
	int		err;

	err = 0;
	if (line[0] == '#')
		return ;
	temp = ft_strsplit(line, ' ');
	if (lenght_of_array(temp) == 3)
	{
		lem_in_add_room(lem_in, temp[0], check_for_integer(temp[1]),
			check_for_integer(temp[2]));
		err = 1;
	}
	ft_free_array(temp);
	temp = ft_strsplit(line, '-');
	if (lenght_of_array(temp) == 2)
	{
		lem_in_add_link(lem_in, temp[0], temp[1]);
		lem_in_add_link(lem_in, temp[1], temp[0]);
		err = 1;
	}
	ft_free_array(temp);
	if (err == 0)
		handle_error(lem_in, "error adding rooms and links\n");
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
		if (lem_in->start_name != NULL)
			handle_error(lem_in, "start room already defined\n");
		lem_in->start = 1;
		return ; // (ft_putstr("##start\n"));
	}
	if (ft_strcmp(line, "##end") == 0)
	{
		if (lem_in->end_name != NULL)
			handle_error(lem_in, "end room already defined\n");
		lem_in->end = 1;
		return ; // (ft_putstr("##end\n"));
	}
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (lem_in->start == 1)
		lem_in->start_name = ft_strsub(line, 0, i);
	else if (lem_in->end == 1)
		lem_in->end_name = ft_strsub(line, 0, i);
	lem_in->start = 0;
	lem_in->end = 0;
}

void	handle_room_print(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}

void	handle_ant_print(t_lem_in *lem_in, char *buf)
{
	lem_in->ants_count = ft_atoi(buf);
	ft_putnbr(lem_in->ants_count);
	ft_putchar('\n');
}

/*
*	Read the lem-in file and create a t_lem_in structure.
*/
void	get_lem_in(t_lem_in *lem_in)
{
	int		read;
	char	*buf;

	read = get_next_line(0, &buf);
	if (read == 0 || read == -1 || buf == NULL)
		handle_error(lem_in, "error reading lem_in\n");
	if (is_number(buf) == 1)
		handle_ant_print(lem_in, buf);
	else
		handle_error(lem_in, "no ants found\n");
	ft_strdel(&buf);
	read = get_next_line(0, &buf);
	while (read != 0 && ft_strcmp("", buf) != 0)
	{
		handle_room_print(buf);
		handle_start_end(lem_in, buf);
		add_to_lem_in(lem_in, buf);
		ft_strdel(&buf);
		read = get_next_line(0, &buf);
	}
	read = get_next_line(0, &buf);
	if (read == 1)
		handle_error(lem_in, "error lem_in not in correct format\n");
	ft_strdel(&buf);
}


int	main(int argc, char **argv)
{
	t_lem_in	*lem_in;

	if (argc != 1)
	{
		ft_printf("Usage: ./lem_in \"stdin\"\n");
		if (argv[0] == NULL)
			return (0);
		return (0);
	}
	lem_in = lem_in_init();
	if (!lem_in)
		return (0);
	get_lem_in(lem_in);
	ft_putchar('\n');
	check_lem_in(lem_in);
	do_lem_in(lem_in);
	free_lem_in(lem_in);
	return (0);
}



/*
int	main(int argc, char **argv)
{
	t_lem_in	*lem_in;

	if (argc != 1)
	{
		ft_printf("Usage: ./lem_in \"stdin\"\n");
		if (argv[0] == NULL)
			return (0);
		return (0);
	}
	lem_in = lem_in_init();
	if (!lem_in)
		return (0);
	clock_t	start = clock();
	get_lem_in(lem_in);
	clock_t stop_1 = clock();
	double elapsed = (double)(stop_1 - start) * 1000.0 / CLOCKS_PER_SEC;

	check_lem_in(lem_in);
	do_lem_in(lem_in);
	
	clock_t	stop_final = clock();
	double	elapsed_2 = (double)(stop_final - start) * 1000.0 / CLOCKS_PER_SEC;

	printf("paths: %d \n", lem_in->paths_count);
	printf("START ROOM in char: %s \n", lem_in->start_name);
	printf("END ROOM in char: %s \n", lem_in->end_name);
	printf("Get_lem_in elapsed in ms: %f\n", elapsed);

	printf("Total elapsed in ms: %f\n", elapsed_2);
	free_lem_in(lem_in);
	return (0);
}

*/