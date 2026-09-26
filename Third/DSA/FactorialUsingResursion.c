//WAP TO FIND FACTORIAL OF NATURAL NUMBER
// USING RECUSRISON

#include<stdio.h>

int Fact(int a);

int main(){
    int n = 0;
    printf("\n Enter the number to find factorial = ");
    scanf("%d",&n);
    printf("\n factorial of %d is %d " , n , Fact(n));
    return 0;
}

int Fact(int n ){
    if(n <= 1){ return 1;}
    else{return n*Fact(n-1);}
}