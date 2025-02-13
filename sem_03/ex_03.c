#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 2
#define MAX_COLUMNS 3

/*
void    init_array(int arr[], int num)
{
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        arr[i] = num;
    }
}

void    fill_array(int arr[])
{
    int num;

    printf("please input your num to fill the array: ");
    scanf(" %d", &num);
    init_array(arr, num);
}

void    print_array(int arr[])
{
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        printf("index: %d num:%d\n", i, arr[i]);
    }
}

int main()
{
    int arr[MAX_COLUMNS];

    init_array(arr, 0);

    print_array(arr);

    fill_array(arr);

    print_array(arr);
}*/

/*
void    init_matrix(int matrix[][MAX_COLUMNS], int num)
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_ROWS; j++)
        {
            matrix[i][j] = num;
        }
    }
}

void    print_matrix(int matrix[][MAX_COLUMNS])
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_ROWS; j++)
        {
           printf("index[%d][%d], num: %d\n", i, j, matrix[i][j]);
        }
    }
}

int main()
{
    int matrix[MAX_ROWS][MAX_COLUMNS];

    init_matrix(matrix, 0);

    print_matrix(matrix);
}*/

int *create_dyn_array(int size)
{
    return((int *)malloc(size * sizeof(int)));
}

int main()
{
    int *arr;
    int size;

    size = 10;
    arr = create_dyn_array(size);
    for (int i = 0; arr[i]; i++)
    {
        printf ("%d\n", arr[i]);
        i++;
    }
    free(arr);
}
