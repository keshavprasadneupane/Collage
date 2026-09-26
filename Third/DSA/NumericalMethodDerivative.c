



#include<stdio.h>
#define Fx(x) ((2*x*x)+1)

float Function(float x){
    return Fx(x);
}

float FirstDerivative(float x, float h){
    return (Function(x + h) - Function(x))/h;
}

int main(){
    float x = 1, h = 0.01f;
    printf("the first derivative = %f ",FirstDerivative(x,h));
    return 0;
}