#include <stdio.h>
int main(){
int a = 5, b = 2;
b = b + 7;
a *= b;
a = b - a;
printf("%d, %d", a, b);
}
