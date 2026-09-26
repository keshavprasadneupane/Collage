#include<stdio.h>
#include<math.h>

#define fx (2*x*x - 7*x + 3)
#define fixedF (pow(((7*(x) + 3) / 2.0), (1.0 / 3.0))) 
// answer is 3 and 1/2

float Limit(float n, float e ){
    return (float)((float)((int)(n/e)) * e);
}
float Func(float x){return fx;}

float FixedFLoatFunc(float x){ return fixedF;}

float MEthodFixedFloat(float a, float precision){
    float b = 0, decision = 0;
    do{
        decision = a;
        b = Limit(FixedFLoatFunc(a),precision);
        a = b;
    }while(decision != a);
    return a;
}

int main(){
    float a =0 ,  precision = 0.1f;
    printf("\nEnter initial guess  =  ");
    scanf("%f",&a);
    printf("\nenter precision, must be like 0.00001  = ");
    scanf("%f",&precision);
    float result = MEthodFixedFloat(a,precision);
    printf("\nthe Anwer for a = %f with precision = %f  = %f \n",
        a,precision,result);

    printf("this algo gives converging point not the actual roots");
    return 0;
}