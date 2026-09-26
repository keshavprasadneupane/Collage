#include<stdio.h>
// Sample Points 
// (1,2), (2,4),(3,6),(4,8) 
// x = 2.5, result = 5
typedef struct Vec4{
    float a;
    float b;
    float c;
    float d;
}Vector4;

Vector4 CreateVector4(float a, float b, float c, float d){
    Vector4 v;
    v.a = a; v.b = b;
    v.c = c; v.d = d;
    return v;
}

float deviation(float x1, float x2 , float y1 , float y2){
    return (y2 - y1)/(x2 - x1);
}

Vector4 Divide(Vector4 X , Vector4 Y){
    float d10 = deviation(X.a , X.b , Y.a , Y.b);
    float d11 = deviation(X.b , X.c , Y.b , Y.c);
    float d12 = deviation(X.c , X.d , Y.c , Y.d);
    float d20 = deviation(X.a , X.c , d10 ,d11);
    float d21 = deviation(X.b , X.d , d11 ,d12);
    float d30 = deviation(X.d,X.a ,d21, d20);
    printf("corrosponding y values = %f,%f,%f,%f",Y.a,d10,d20,d30);
    return CreateVector4(Y.a , d10 , d20 ,d30);
}

float NewtonDivideAndDifference(Vector4 X , Vector4 Y , float x){
    Vector4 CY = Divide(X,Y);
    float result = CY.a + (x - X.a) * CY.b + 
                    (x-X.a)*(x-X.b)*CY.c + (x - X.a)*(x-X.b)*(x-X.c) * CY.d;
    return result;
}

int main(){
    Vector4 X ,Y;
    float x = 0;
    printf("\nenter x1 , y1  = ");
    scanf("%f %f",&X.a,&Y.a);
    printf("enter x2 , y2  = ");
    scanf("%f %f",&X.b,&Y.b);
    printf("enter x3 , y3  = ");
    scanf("%f %f",&X.c,&Y.c);
    printf("enter x4 , y4  = ");
    scanf("%f %f",&X.d,&Y.d);
    printf("enter interpolatiing point ,x = ");
    scanf("%f",&x);
    float interpolated = NewtonDivideAndDifference(X,Y,x);
    printf("\nInterpolated value = %f",interpolated);
    return 0;
}