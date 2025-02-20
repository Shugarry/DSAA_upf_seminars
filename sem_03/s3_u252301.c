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
	while (fscanf(file, "%s %d %d ", tmp.name, &tmp.org, &tmp.dst) == 3)
	{
		if (!tmp.name[0] || tmp.org == -1 || tmp.dst == -1)
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
	return (list);
}

void	move(Elevator *elevator, int num_waiting_clients, Client *waiting_clients)
{

}

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
		if (swapped)
			break ;
	}
}

void	order_dst(Client **c, int in_elevator)
{
	Client	tmp;
	Client	*clients = *c;
	int		diff_a, diff_b;
	int		swapped = 0;

	for (int i = 0; i < in_elevator - 1; i++)
	{
		for (int j = 0; j < in_elevator - 1 - i; j++)
		{
			diff_a = abs(floor - clients[j].dst);
			diff_b = abs(floor - clients[j + 1].dst);
			if (diff_a > diff_b)
			{
				tmp = clients[j];
				clients[j] = clients[j + 1];
				clients[j + 1] = tmp;
				swapped = 1;
			}
		}
		if (swapped)
			break ;
	}
}

void	board(Elevator *elevator, Client **w_c, int *waiting)
{
	Client	*waiting_clients = w_c;
	Client	*tmp
	int		boarding = 0;

	while (elevator->floor == waiting_clients[boarding].org)
		boarding++;
	*waiting -= boarding;
	tmp = (Clients *)malloc(sizeof(Clients) * (elevator->num_clients + boarding));
	for (int i = 0; i < elevator->num_clients; i++)
	{
		tmp[i] = elevator->clients[i];
	}
}

int	main(void)
{
	Elevator	elevator = {0, 0, NULL};
	int			num_waiting;
	Client		*waiting_clients = read_clients(num_waiting);

	while(waiting_clients && elevator.clients)
	{
		order_org(&waiting_clients, num_waiting);
		if (elevator.floor == waiting_clients[0].org)
			board(&elevator, &waiting_clients);
		order_dst(&elevator->clients, elevator.num_clients);
		if (elevator.floor == elevator->clients.dst)
			serve(&elevator, waiting_clients);
		move();
	}
}
