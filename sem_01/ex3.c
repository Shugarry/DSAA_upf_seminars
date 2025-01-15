#include <stdio.h>
int main(){
int a = 11;
a = a<<6;
a &= (1<<6);
int b = 1<<5;
a = (a|b)>>4;
printf("%d", a);
}
