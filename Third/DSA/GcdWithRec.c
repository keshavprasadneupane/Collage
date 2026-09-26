//WAP TO FIND GREATEST COMMON DIVISOR USING RECUSRISON
#include<stdio.h>
int GCD(int a , int b);

int main(){
    int n = 0 , n1 = 0;
    printf("\n Enter two number to find GCD = ");
    scanf("%d %d",&n ,&n1);
    printf("\n GCD of %d and %d is %d " , n , n1 , GCD(n ,n1));
    return 0;
}

int GCD(int a , int b){
    if(b == 0){ return a;}
    else{return GCD(b,a%b);}
}