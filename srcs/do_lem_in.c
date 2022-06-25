void	insert(int data) 
{
   queue[++rear] = data;
   queueItemCount++;
}

int		removeData()
{
   queueItemCount--;
   return (queue[front++]);
}

int		isQueueEmpty()
{
   return queueItemCount == 0;
}

void	do_lem_in(t_lem_in *lem_in)
{
	//queue variables

	int queue[MAX];
	int rear = -1;
	int front = 0;
	int queueItemCount = 0;

	print_rooms(lem_in);
	print_links(lem_in);
	print_ants(lem_in);
	// print_moves(lem_in);
		// while ()
	ft_printf("room_name : %s\n" ,lem_in->rooms->name);
	ft_printf("ants : %i\n" ,lem_in->ants->ant_id);
}