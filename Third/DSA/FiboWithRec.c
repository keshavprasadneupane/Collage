//WAP TO FIND FIBONACCI SERIES NUMBER AT NTH PLACE
//USING RECUSRISON

#include<stdio.h>
int Fibo(int n);

int main(){
    int n = 0;
    printf("\n Enter the number to find Fibo = ");
    scanf("%d",&n);
    printf("\n factorial of %d is %d " , n , Fibo(n));
    return 0;
}

int Fibo(int n){
    if (n <= 1){return 1;}
    else { return Fibo(n-1)+Fibo(n-2);}
}