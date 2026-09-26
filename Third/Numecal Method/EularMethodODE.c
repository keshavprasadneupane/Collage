#include<stdio.h>
// diff eqn for eular method 
#define dfxy (2*x*x - 7*x*y + 3*y)
// initial condition y(0) = 2
// finding  = y(1) and h = 0.2
// answer = 1.957....

float Func(float x , float y){return dfxy;}

float EularMethodOde(float x0, float y0, float h,float x,float precision){
    float m = 0 , ynext = 0;
    float iteration = (x - x0)/h;
    for (float i = x0 ; i < x ; i = i + h){
        m = Func(i , y0);
        ynext = y0 + m * h;
        y0 =  ynext;
    }
    return y0;
}

int main(){
    float a =0, b =0 ,x = 0, h = 0 ,precision = 0.001f;
    printf("\nEnter initial condition x0,y0 ,h =  ");
    scanf("%f %f %f",&a,&b,&h);
    printf("enter which point value u want to find = ");
    scanf("%f",&x);
    float result = EularMethodOde(a,b,h,x,precision);
    printf("\nthe Anwer= %f \n", result);
    return 0;
}