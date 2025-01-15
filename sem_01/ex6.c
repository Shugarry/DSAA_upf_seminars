#include <stdio.h>
int main(){
int serie[8];
serie[0] = 1;
for(int i=1; i<8; ++i){
if(i < 3){
serie[i] = (serie[i-1]+i)%4;
}
else if(i < 6){
serie[i] = (serie[i-1]+i)%3;
}
else{
serie[i] = (serie[i-1]+i)%2;
}
printf("%d ", serie[i]);
}
}
