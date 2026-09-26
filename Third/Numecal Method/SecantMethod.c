#include<stdio.h>

#define fx (2*x*x - 7*x + 3)
// answer is 3 and 1/2

float Limit(float n, float e ){
    return (float)((float)((int)(n/e)) * e);
}
float Func(float x){return fx;}

float Secant(float a,float b ,float precision){
    float anext = 0, decision = 0 ;
    float fa = 0, fb = 0 , fm = 0;
    do{
        decision = a;
        fa = Func(a);
        fb = Func(b);
        anext = Limit((b*fa - a * fb)/(fa - fb),precision);
        b = a;
        a = anext;
    }while(decision != a);
    return a;
}

int main(){
    float a =0, b =0,  precision = 0.1f;
    printf("\nEnter initial guess a,b =  ");
    scanf("%f %f",&a,&b);
    printf("enter precision, must be like 0.00001  = ");
    scanf("%f",&precision);
    float result = Secant(a,b,precision);
    printf("the Anwer for a = %f with precision = %f  = %f \n",
        a,precision,result);
    return 0;
}