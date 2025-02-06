#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_MOVIES 12
#define MAX_VOTES 50

typedef enum
{
	Action,
	Adventure,
	Animation,
	Comedy,
	Documentary,
	Drama,
	Fantasy,
	Horror,
	SciFi,
	Unknown = -1
}	Category;

typedef struct
{
	char		name[20];
	int			score;
	Category	cat_a;
	Category	cat_b;
}	Movie;

void	exit_msg(char *str, int status)
{
	printf("%s", str);
	exit(status);
}

Category	get_from_string(char category_name[])
{
	if (!strcmp(category_name, "Action"))
		return (Action);
	else if (!strcmp(category_name, "Adventure"))
		return (Adventure);
	else if (!strcmp(category_name, "Animation"))
		return (Animation);
	else if (!strcmp(category_name, "Comedy"))
		return (Comedy);
	else if (!strcmp(category_name, "Documentary"))
		return (Documentary);
	else if (!strcmp(category_name, "Drama"))
		return (Drama);
	else if (!strcmp(category_name, "Fantasy"))
		return (Fantasy);
	else if (!strcmp(category_name, "Horror"))
		return (Horror);
	else if (!strcmp(category_name, "SciFi"))
		return (SciFi);
	else
		return (Unknown);
}

void	voting(Category c, Movie *movies, int num_movies)
{
	for (int i = 0; i < num_movies; i++)
	{
		if (c == movies[i].cat_a || c == movies[i].cat_b)
			movies[i].score++;
	}
}

void	print_movie(Movie m)
{
	printf("Name: %s\nScore: %d\n", m.name, (m.score * 10));
}

void	top_5_movies(Movie *movies, int num_movies)
{
	int		swapped;
	Movie	tmp;

	for (int i = 0; i < num_movies - 1; i++)
	{
		swapped = 0;
		for (int j = 0; j < num_movies - i - 1; j++)
		{
			if (movies[i].score > movies[i + 1].score)
			{
				tmp = movies[i];
				movies[i] = movies[i + 1];
				movies[i + 1] = tmp;
				swapped = 1;
			}
		}
		if (!swapped)
			break;
	}

	for (int i = 0; i < 5; i++)
	{
		print_movie(movies[i]);
	}
}

int main()
{
	Movie	movies[MAX_MOVIES];
	int		n_movies;
	int		n_votes;
	char	tmp[20];
	char	cat_a[20];
	char	cat_b[20];

	printf("Input amount of movies (6 - 12): ");
	scanf(" %d", &n_movies);
	printf("Input %d movies (Format: Movie Category Category):\n", n_movies);
	for	(int i = 0; i < n_movies; i++)
	{
		scanf(" %s %s %s", movies[i].name, cat_a, cat_b);
		movies[i].cat_a = get_from_string(cat_a);
		movies[i].cat_b = get_from_string(cat_b);
		movies[i].score = 0;
	}
	printf("Input amount of votes (2 - 50): ");
	scanf(" %d", &n_votes);
	printf("Input %d votes (Format: Category):\n", n_votes);
	for	(int i = 0; i < n_votes; i++)
	{
		scanf(" %s", tmp);
		voting(get_from_string(tmp), movies, n_movies);
	}
	top_5_movies(movies, n_movies);
}
