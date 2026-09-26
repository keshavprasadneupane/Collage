#include<stdio.h>

void Tower(int n , char s , char a , char d);

int main(){
    int n = 4;
    printf("\n\n\nthe order for %d disks are\n",n);
    Tower(n, 's', 'a','d');
    return 0 ;
}

void Tower(int n , char s, char a , char d){
    if(n == 1 ){
        printf(" moved disc %d from %c to %c\n ", n,s,d);
    }else{
        Tower(n-1 , s ,d,a);
        printf("moved dist %d from %c to %c \n", n-1 ,s,d);
        Tower(n-1 , a,s,d);
    }
}