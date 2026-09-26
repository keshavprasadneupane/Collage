#include<stdio.h>

#define fx (2*x*x - 7*x + 3)
// answer is 3 and 1/2
float Limit(float n, float e ){
    return (float)((float)((int)(n/e)) * e);
}
float Func(float x){return fx;}

float Derivative(float x , float h){
    return (Func(x + h) - Func(x))/h;
}

float NewtonRapson(float a , float precision){
    float anext= 0 , decision = 0;
    float fa = 0 , dfa = 0;
    do{
        decision = a;
        fa = Func(a);
        dfa = Derivative(a,precision);
        anext = Limit(a - (fa/dfa),precision);
        a = anext;
    }while(decision != a);
    return a;
}

int main(){
    float a =0,  precision = 0.1f;
    printf("\nEnter initial guess a =  ");
    scanf("%f",&a);
    printf("\nenter precision,must be like 0.00001  = ");
    scanf("%f",&precision);
    float result = NewtonRapson(a,precision);
    printf("\nthe Anwer for a = %f with precision = %f  = %f \n",
        a,precision,result);
    return 0;
}