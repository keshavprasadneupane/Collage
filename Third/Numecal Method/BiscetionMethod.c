#include<stdio.h>
#define fx (2*x*x - 7*x + 3)
// answer is 3 and 1/2
float Limit(float n, float e ){
    return (float)((float)((int)(n/e)) * e);
}
float Func(float x){return fx;}
float Bisection(float a , float b , float precision){
    float m = 0, decision = 0;
    float fa = 0,fb = 0 , fm = 0;
    do{
        decision = m;
        m = Limit((a + b)/2 , precision);
        fa = Limit(Func(a),precision);
        fb = Limit(Func(b),precision);
        fm = Limit(Func(m),precision);
        if(fm == 0){return m;}
        if(fa * fm < 0){b = m;}
        else if (fb * fm < 0) { a = m;}
    }while(decision != m);
    return m;
}

int main(){
    float a =0,b=0 ,  precision = 0.1f;
    printf("\nEnter a  and b  =  ");
    scanf("%f %f",&a,&b);
    printf("enter precision precision must be like 0.00001  = ");
    scanf("%f",&precision);
    float result = Bisection(a,b,precision);
    printf("the Anwer for a = %f and b = %f with precision = %f  = %f \n",
        a,b,precision,result);
    return 0;
}