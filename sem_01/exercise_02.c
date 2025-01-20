#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
	char	*words[50] = {
		"AgrIcUlture", 
		"WorldwIdE!", 
		"HllWrld", 
		"#***.!&+¿?,$", 
		"A",
		"Bb", 
		"B", 
		"Ba", 
	};
    int flag;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < (int)strlen(words[i]); j++)
        {
            if (words[i][j] == 'A' || words[i][j] == 'a' || words[i][j] == 'E' ||
				words[i][j] == 'e' || words[i][j] == 'I' || words[i][j] == 'i' ||
				words[i][j] == 'O' || words[i][j] == 'o' || words[i][j] == 'U' ||
				words[i][j] == 'u')
                flag = 1;
        }
        if (flag || strlen(words[i]) == 1)
            printf("Word %d = Human", i);
        else    
            printf("Word %d = Alien", i);
        flag = 0;
        printf("\n");
    }
    return (0);
}
