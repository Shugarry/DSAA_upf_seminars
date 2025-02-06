#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_MOVIES 12
#define MAX_VOTES 50
#define STR_SIZE 20

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
}	Category;

typedef struct
{
	char		name[20];
	int			score;
	Category	cat_a;
	Category	cat_b;
}	Movie;

// added my own function to exit with error msg, just in case of input error
void exit_msg(char *str, int status)
{
	printf("%s", str);
	exit(status);
}

// use strcmp() to figure out which category is chosen, checks for both
// Category and "Category" (quoted), just in case the input is quoted or not,
// its not really clear how i should do it in the pdf. Returns (-1) by default
// just to get around compiler warning
Category	get_from_string(char *category_name)
{
	if (!strcmp(category_name, "Action") || !strcmp(category_name, "\"Action\""))
		return (Action);
	if (!strcmp(category_name, "Adventure") || !strcmp(category_name, "\"Adventure\""))
		return (Adventure);
	if (!strcmp(category_name, "Animation") || !strcmp(category_name, "\"Animation\""))
		return (Animation);
	if (!strcmp(category_name, "Comedy") || !strcmp(category_name, "\"Comedy\""))
		return (Comedy);
	if (!strcmp(category_name, "Documentary") || !strcmp(category_name, "\"Documentary\""))
		return (Documentary);
	if (!strcmp(category_name, "Drama") || !strcmp(category_name, "\"Drama\""))
		return (Drama);
	if (!strcmp(category_name, "Fantasy") || !strcmp(category_name, "\"Fantasy\""))
		return (Fantasy);
	if (!strcmp(category_name, "Horror") || !strcmp(category_name, "\"Horror\""))
		return (Horror);
	if (!strcmp(category_name, "SciFi") || !strcmp(category_name, "\"SciFi\""))
		return (SciFi);
	exit_msg("Category does not exist\n", 1);
	return (-1);
}

// loop that adds 1 to score when category voted is equal to a category in the
// movie structure
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

// bubble sorts the array of movies and then compares them by checking their
// score and sorting by biggest to smallest. uses strcmp too to check lexical
// order to sort. Then prints the first 5 movies in the array
void	top_5_movies(Movie *movies, int num_movies)
{
	int		swapped;
	Movie	tmp;

	for (int i = 0; i < num_movies - 1; i++)
	{
		swapped = 0;
		for (int j = 0; j < num_movies - i - 1; j++)
		{
			if (movies[j].score < movies[j + 1].score || 
    			(movies[j].score == movies[j + 1].score && 
     			strcmp(movies[j].name, movies[j + 1].name) > 0))
			{
				tmp = movies[j];
				movies[j] = movies[j + 1];
				movies[j + 1] = tmp;
				swapped = 1;
			}
		}
		if (!swapped)
			break;
	}

	printf("Top 5 movies:\n");
	for (int i = 0; i < 5 && i < num_movies; i++)
		print_movie(movies[i]);
}

// main includes prompts to know what needs to be inputted and also an exit
// function on wrong input
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
	if (n_movies < 6)
		exit_msg("Movie amount out of bounds\n", 1);
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
	if (n_votes < 2)
		exit_msg("Amount of votes out of bounds\n", 1);
	printf("Input %d votes (Format: Category):\n", n_votes);
	for	(int i = 0; i < n_votes; i++)
	{
		scanf(" %s", tmp);
		voting(get_from_string(tmp), movies, n_movies);
	}
	top_5_movies(movies, n_movies);
}
