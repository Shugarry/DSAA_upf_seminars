#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int	remainder;
    int	num;
   
    num = pow(10, 9) + 7;
    remainder = num % 7;
    switch (remainder)
    {
        case 0:
            printf("Wednesday"); break;
        case 1:
            printf(" Thursday"); break;
        case 2:
            printf("Friday"); break;
        case 3:
            printf("Saturday"); break;
        case 4:
            printf("Sunday"); break;
        case 5:
            printf("Monday"); break;
        case 6:
            printf("Tuesday"); break;
    }
    printf("\n");
    return (0); 
}
