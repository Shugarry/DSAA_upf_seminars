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

Client	*append_client(Client *list, Client *new_client, int num_clients)
{
	Client	*tmp;

	if (num_clients == 1)
	{
		tmp = new_client;
		return (tmp);
	}

	tmp = (Client *)malloc(num_clients * sizeof(Client));
	if (!tmp)
	{
		printf("malloc failure");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < num_clients - 2; i++)
		tmp[i] = list[i];
	free(list);
	tmp[num_clients - 1] = *new_client;
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
	while (fscanf(file, " %s %d %d", tmp.name, &tmp.org, &tmp.dst) == 3);
	{
		/*
		if (!tmp.name[0] || tmp.org == -1 || tmp.dst == -1)
		{
			printf("Parsing error, please make sure that your clients.txt file is correct\n");
			exit(EXIT_FAILURE);
		}
		*/
		(*num_clients)++;
		list = append_client(list, &tmp, *num_clients);
		tmp.name[0] = '\0';
		tmp.org = -1;
		tmp.dst = -1;
	}
}

int main()
{
	Elevator elevator = {0, 0, NULL};

	elevator.clients = read_clients(&elevator.num_clients);
	for (int i = 0; i < elevator.num_clients; i++)
	{
		printf("client %d -> name: %s, org: %d, dst: %d\n", i, elevator.clients[i].name, elevator.clients[i].org, elevator.clients[i].org);
	}
}
