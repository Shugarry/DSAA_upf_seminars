#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_TEAMS 6

// I created a Match data structure which holds two team variables to simulate
// an actual match which would be played
typedef struct
{
	int team1;
	int team2;
} Match;

void generate_matches(Match matches[], int n)
{
	int match_index = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			matches[match_index].team1 = i;
			matches[match_index].team2 = j;
			match_index++;
		}
	}
}

// This recursive function implements backtracking alongside the recurison like
// asked for in the PDF to find all of the possible solutions. The way it works
// is by creating all possible scenarios of how the matches can end between two
// teams, then adding 1 or 0 on the recursive return if the match has the same
// scores.
//
// After every time the recursion is done, backtracking is implemented so we go
// back to the original state of scores, to begin from the beginning. In
// the end, all of the different solutions are found.
int count_solutions(Match matches[], int match_index, int total_matches, int current_scores[], int final_scores[], int n)
{
	int count = 0;
	Match current_match = matches[match_index];
	int team1 = current_match.team1;
	int team2 = current_match.team2;

	if (match_index == total_matches) // loop to check if a valid solution has been found
	{
		for (int i = 0; i < n; i++)
		{
			if (current_scores[i] != final_scores[i])
				return 0;
		}
		return 1;
	}

	// team 1 wins
	current_scores[team1] += 3;
	count += count_solutions(matches, match_index + 1, total_matches, current_scores, final_scores, n);
	current_scores[team1] -= 3;

	// draw
	current_scores[team1] += 1;
	current_scores[team2] += 1;
	count += count_solutions(matches, match_index + 1, total_matches, current_scores, final_scores, n);
	current_scores[team1] -= 1;
	current_scores[team2] -= 1;

	// team 2 wins
	current_scores[team2] += 3;
	count += count_solutions(matches, match_index + 1, total_matches, current_scores, final_scores, n);
	current_scores[team2] -= 3;

	return count;
}

int main() {
	int		n;
	int		total_matches;
	int		final_scores[MAX_TEAMS];
	Match	matches[total_matches];
	int		current_scores[MAX_TEAMS] = {0};

	scanf("%d", &n); // to get N teams between 3 and 6 according to constraints
	if (n < 3 || n > 6)
	{
		printf("invalid amount of teams must be between 3 and 6\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; i++) // same for Si scores
	{
		scanf("%d", &final_scores[i]);
		if (final_scores[i] < 0 || final_scores[i] > 15)
		{
			printf("invalid score amount, must be between 0 and 15");
			exit(EXIT_FAILURE);
		}
	}

	total_matches = n * (n - 1) / 2; // amount of matches played according to constraints

	generate_matches(matches, n); // creates all possible matches that can be played

	printf("%d\n", count_solutions(matches, 0, total_matches, current_scores, final_scores, n));

	return 0;
}
