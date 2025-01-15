#include <stdio.h>
#include <string.h>
int main(){
char word[12] = "John Doe";
word[0]='X';
word[5]='H';
word[9]='Y';
word[10]='u';
printf("%s, %ld", word, strlen(word));
}
