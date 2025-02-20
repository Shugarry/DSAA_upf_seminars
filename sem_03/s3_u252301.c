#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	char	name[11];
	int		org;
	int		dst;
}	Client;

typedef struct
{
	int		floor;
	int		num_clients;
	Client	*clients;
}	Elevator;

// append_client adds a client to the end of a new list and frees the old one 
Client	*append_client(Client *list, Client new_client, int num_clients)
{
	Client	*tmp;

	tmp = (Client *)malloc(num_clients * sizeof(Client));
	if (!tmp)
	{
		printf("malloc failure\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < num_clients - 1; i++)
		tmp[i] = list[i];
	free(list);
	tmp[num_clients - 1] = new_client;
	return (tmp);
}

// read_clients scans the file and adds the variables to an array of Client 1 by 1.
// Uses append_client to add each one to the end
Client	*read_clients(int *num_clients)
{
	FILE	*file = fopen("clients.txt", "r");
	Client	*list = NULL;
	Client	tmp = { "\0", -1, -1 };

	*num_clients = 0;
	if (!file)
	{
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}
	while (fscanf(file, " %10s %d %d", tmp.name, &tmp.org, &tmp.dst) == 3)
	{
		if (!tmp.name[0] || tmp.org < 0 || tmp.dst < 0)
		{
			printf("Parsing error, please make sure that your clients.txt file is correct\n");
			exit(EXIT_FAILURE);
		}
		(*num_clients)++;
		list = append_client(list, tmp, *num_clients);
		tmp.name[0] = '\0';
		tmp.org = -1;
		tmp.dst = -1;
	}
	fclose(file);
	return (list);
}

// orders the client array by order of smallest to largest in origin floor amount
void	order_org(Client **c, int waiting)
{
	Client	tmp;
	Client	*clients = *c;
	int		swapped = 0;

	for (int i = 0; i < waiting - 1; i++)
	{
		for (int j = 0; j < waiting - 1 - i; j++)
		{
			if (clients[j].org > clients[j + 1].org)
			{
				tmp = clients[j];
				clients[j] = clients[j + 1];
				clients[j + 1] = tmp;
				swapped = 1;
			}
		}
		if (!swapped)
			break ;
	}
}

// orders the client array by order of smallest to largest in distance to
// elevator floor amount
void	order_dst(Elevator *elevator, int in_elevator)
{
	Client	tmp;
	Client	*clients = elevator->clients;
	int		diff_a, diff_b;
	int		swapped = 0;

	for (int i = 0; i < in_elevator - 1; i++)
	{
		for (int j = 0; j < in_elevator - 1 - i; j++)
		{
			diff_a = abs(elevator->floor - clients[j].dst);
			diff_b = abs(elevator->floor - clients[j + 1].dst);
			if (diff_a > diff_b)
			{
				tmp = clients[j];
				clients[j] = clients[j + 1];
				clients[j + 1] = tmp;
				swapped = 1;
			}
		}
		if (!swapped)
			break ;
	}
}

// Boards a client or clients onto the elevator by calculating the size of both
// new lists (waiting clients and the ones in elevator) and then copies the ones
// from the waiting clients that are supposed to board to the end of the elevator
// list. frees the old lists to avoid memory leaks.
void	board(Elevator *elevator, Client **w_c, int *waiting)
{
	Client	*waiting_clients = *w_c;
	Client	*new_waiting = NULL;
	Client	*tmp;
	int		boarding = 0;

	while (boarding < *waiting && elevator->floor == waiting_clients[boarding].org)
		boarding++;
	if (*waiting)
		*waiting -= boarding;

	tmp = (Client *)malloc(sizeof(Client) * (elevator->num_clients + boarding));
	if (!tmp)
	{
		printf("malloc failure\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0, j = 0; i < elevator->num_clients + boarding; i++)
	{
		if (i < elevator->num_clients)
			tmp[i] = elevator->clients[i];
		else
		{
			tmp[i] = waiting_clients[j];
			printf("Boarding %s\n", waiting_clients[j].name);
			j++;
		}
	}
	free(elevator->clients);
	elevator->clients = tmp;
	
	new_waiting = (Client *)malloc((*waiting) * sizeof(Client));
	if (!new_waiting)
	{
		printf("malloc failure\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < *waiting; i++)
	{
		new_waiting[i] = waiting_clients[i + boarding];
	}
	free(waiting_clients);
	(*w_c) = new_waiting;
	elevator->num_clients += boarding;
}

// Removes clients from the elevator and creates new arrays and frees the previous
// ones
void serve(Elevator *elevator)
{
	int exited = 0;
	Client *tmp = NULL;
	int new_num = 0;

	while (exited < elevator->num_clients && elevator->clients[exited].dst == elevator->floor)
	{
		printf("Serving %s\n", elevator->clients[exited].name);
		exited++;
	}

	if (exited == 0)
		return ;
	new_num = elevator->num_clients - exited;

	if (new_num > 0)
	{
		tmp = malloc(new_num * sizeof(Client));
		if (!tmp)
		{
			printf("malloc failure\n");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < new_num; i++)
			tmp[i] = elevator->clients[exited + i];
	}

	free(elevator->clients);
	elevator->clients = tmp;
	elevator->num_clients = new_num;
}

// finds the highest floor that the elevator has to go to
int	get_highest(Client *waiting_clients, int num_waiting)
{
	int	highest = 0;

	for (int i = 0; i < num_waiting; i++)
	{
		if (highest < waiting_clients[i].org)
			highest = waiting_clients[i].org;

		if (highest < waiting_clients[i].dst)
			highest = waiting_clients[i].dst;
	}
	return (highest);
}

// boards and serves all clients by going up once to the "highest" floor
// calculated by get_highest and then down once to serve the remaining clients
// all clients are served in the end and there are no memory leaks
//
// ADDITIONAL NOTE: I saw no point in making the move() function because my
// implementation didn't require it, its function is copied by the loops in main
//
// SECOND NOTE: the other functions asked by the pdf aren't declared exactly like in
// pdf, for example i use double pointers in the board() function and serve
// returns void. This is because i felt like the memory management is a bit better
// and easier to understand this way, either way the program works perfectly and
// within the constraints proposed by the PDF

int	main(void)
{
	Elevator	elevator = {0, 0, NULL};
	int			num_waiting;
	Client		*waiting_clients = read_clients(&num_waiting);
	int			highest_floor = get_highest(waiting_clients, num_waiting);
	int			printed_floor = 1;

	for (int i = 0; i <= highest_floor; i++)
	{
		order_org(&waiting_clients, num_waiting);

		if (num_waiting && elevator.floor == waiting_clients[0].org)
		{
			if (i != 0)
				printf("Up %d\n", elevator.floor);
			printed_floor = 1;
			board(&elevator, &waiting_clients, &num_waiting);
		}

		order_dst(&elevator, elevator.num_clients);

		if (elevator.num_clients && elevator.floor == elevator.clients[0].dst)
		{
			if (!printed_floor)
			{
				printf("Up %d\n", elevator.floor);
				printed_floor = 1;
			}
			serve(&elevator);
		}
		printed_floor = 0;
		elevator.floor++;
	}

	order_dst(&elevator, elevator.num_clients);

	for (int i = highest_floor; i >= 0; i--)
	{
		elevator.floor--;
		if (elevator.floor == elevator.clients[0].dst)
		{
			if (i != highest_floor)
				printf("Down %d\n", elevator.floor);
			serve(&elevator);
		}
	}
	free(elevator.clients);
	free(waiting_clients);
}
