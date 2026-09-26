#include<stdio.h>
// diff eqn for eular method 
#define dfxy (2*x*x - 7*x*y + 3*y)
// initial condition y(0) = 2
// finding  = y(1) and h = 0.2
// answer = 1.60....

float Func(float x , float y){return dfxy;}

float HeunsMethodOde(float x0, float y0, float h,float x,float precision){
    float m1 = 0 , m2 = 0, ynext = 0;
    float iteration = (x - x0)/h;
    for (float i = x0 ; i < x ; i = i + h){
        m1 = Func(i , y0);
        m2 = Func(i + h, y0 + m1 * h );
        ynext = y0 + ((m1 + m2) * h / 2.0f);
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
    float result = HeunsMethodOde(a,b,h,x,precision);
    printf("\nthe Anwer= %f \n", result);
    return 0;
}