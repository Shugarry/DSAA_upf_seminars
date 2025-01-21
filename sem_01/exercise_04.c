#include <stdio.h>

typedef struct //player type object with name, left and right hand values.
{
	int		left;
	int		right;
	char	name[20];
} player;

int  play_turn(player *p1, player *p2, char p1_hand, char p2_hand)
{
    if ((p2_hand == 'R' && !p2->right) || (p2_hand == 'L' && !p2->left))
        return (0);
    if (p1_hand == 'L' && !p1->left)
        return (0);
    else if(p1_hand == 'L' && p2_hand == 'L')
        p2->left = p2->left + p1->left;
    else if(p1_hand == 'L' && p2_hand == 'R')
        p2->right = p2->right + p1->left;
    if (p1_hand == 'R' && !p1->right)
        return (0);
    else if(p1_hand == 'R' && p2_hand == 'R')
        p2->right = p2->right + p1->right;
    else if(p1_hand == 'R' && p2_hand == 'L')
        p2->left = p2->left + p1->right;
    if (p1->left > 4)
        p1->left -= 5;
    if (p1->right > 4)
        p1->right -= 5;
    if (p2->left > 4)
        p2->left -= 5;
    if (p2->right > 4)
        p2->right -= 5;
    //printf("p1 left :%d  ", p1->left);
    //printf("p1 right :%d  ", p1->right);
    //printf("p2 left :%d  ", p2->left);
    //printf("p2 right :%d\n", p2->right);
    return (1);
}
//play_turn plays out each turn according to specifications and also checks
//wether each play made is valid and returns either 0 or 1 accordingly. Also,
//at the end of the function

int check_win(player *alice, player *bob)
{
    int bob_pts = 2;
    int alice_pts = 2;

    if (!alice->left)
        alice_pts--;
    if (!alice->right)
        alice_pts--;
    if (!bob->left)
        bob_pts--;
    if (!bob->right)
        bob_pts--;
    if (alice_pts > bob_pts && !bob_pts)
        return (1);
    else if (alice_pts > bob_pts)
        return (3);
    if (bob_pts > alice_pts && !alice_pts)
        return (2);
    else if (bob_pts > alice_pts)
        return (4);
    return (5);
}
//check_win compares alice and bobs hands left at the end of each round and at 
//the end of game, each case (e.g. alice wins and bob has 0 hands left too)
//returns an int from 1 to 5 to separate each case for optimization

int main()
{
	player  alice = {1, 1, "Alice"};
    player  bob = {1, 1, "Bob"};
    int     turns;
    char    person, p1_hand, p2_hand;


    printf("Please input amount of turns (4 - 20): ");
    scanf("%d\n", &turns);

    if (turns < 4 || turns > 20)
    {
        printf("Out of bounds turns. Execute and try again");
            return (0);
    }

    for (int i = 0; i < turns; i++)
    {
        scanf(" %c %c %c", &person, &p1_hand, &p2_hand);
        //printf("%c, %c, %c\n", person, p1_hand, p2_hand);
        if (person == 'A')
        {
            if(!play_turn(&alice, &bob, p1_hand, p2_hand))
            {
                printf("Invalid move!!\n");
                break;
            }
        }
        if (person == 'B')
        {
            if(!play_turn(&bob, &alice, p1_hand, p2_hand))
            {
                printf("Invalid move!!\n");
                break;
            }
        }
        if (check_win(&alice, &bob) < 3)
           break; 
    }

    switch (check_win(&alice, &bob))
    {
        case 1:
            printf("Alice Wins!!\n"); break;
        case 2:
            printf("Bob Wins!!\n"); break;
        case 3:
            printf("Alice Wins!!\n"); break;
        case 4:
            printf("Bob Wins!!\n"); break;
        case 5:
            printf("None Wins\n"); break;
        default:
            break;
    }
}
