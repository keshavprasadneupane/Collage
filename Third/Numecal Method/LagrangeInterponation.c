#include<stdio.h>
// Sample Points 
// (1,2), (2,4),(3,6),(4,8)
// x = 2.5, result = 5
float Inter(float x, float first, float x1, float x2, float x3, float y) {
    return (((x - x1) * (x - x2) * (x - x3)) / ((first - x1) * (first - x2) * (first - x3))) * y;
}

float LagrangeInterpolation(float x1, float x2, float x3, float x4, 
                            float y1, float y2, float y3, float y4, float x) {
    float L1 = Inter(x, x1, x2, x3, x4, y1);  
    float L2 = Inter(x, x2, x1, x3, x4, y2);  
    float L3 = Inter(x, x3, x1, x2, x4, y3);  
    float L4 = Inter(x, x4, x1, x2, x3, y4); 
    return L1 + L2 + L3 + L4;
}

int main(){
    float x1 ,x2,x3,x4 ,y1,y2,y3,y4, x;
    printf("\nenter x1 , y1  = ");
    scanf("%f %f",&x1,&y1);
    printf("enter x2 , y2  = ");
    scanf("%f %f",&x2,&y2);
    printf("enter x3 , y3  = ");
    scanf("%f %f",&x3,&y3);
    printf("enter x4 , y4  = ");
    scanf("%f %f",&x4,&y4);
    printf("enter interpolatiing point ,x = ");
    scanf("%f",&x);
    float interpolated = LagrangeInterpolation(x1,x2,x3,x4,y1,y2,y3,y4,x);
    printf("\nInterpolated value = %f",interpolated);
    return 0;
}